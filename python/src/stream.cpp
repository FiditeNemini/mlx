// Copyright © 2023-2024 Apple Inc.

#include <sstream>

#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/variant.h>

#include "mlx/stream.h"
#include "mlx/utils.h"

namespace mx = mlx::core;
namespace nb = nanobind;
using namespace nb::literals;

// Create the StreamContext on enter and delete on exit.
class PyStreamContext {
 public:
  PyStreamContext(mx::StreamOrDevice s) : _inner(nullptr) {
    if (std::holds_alternative<std::monostate>(s)) {
      throw std::runtime_error(
          "[StreamContext] Invalid argument, please specify a stream or device.");
    }
    _s = s;
  }

  void enter() {
    _inner = new mx::StreamContext(_s);
  }

  void exit() {
    if (_inner != nullptr) {
      delete _inner;
      _inner = nullptr;
    }
  }

 private:
  mx::StreamOrDevice _s;
  mx::StreamContext* _inner;
};

void init_stream(nb::module_& m) {
  nb::class_<mx::Stream>(
      m,
      "Stream",
      R"pbdoc(
      A stream for running operations on a given device.
      )pbdoc")
      .def_ro("device", &mx::Stream::device)
      .def(
          "__repr__",
          [](const mx::Stream& s) {
            std::ostringstream os;
            os << s;
            return os.str();
          })
      .def("__eq__", [](const mx::Stream& s, const nb::object& other) {
        return nb::isinstance<mx::Stream>(other) &&
            s == nb::cast<mx::Stream>(other);
      });

  nb::implicitly_convertible<mx::Device::DeviceType, mx::Device>();

  m.def(
      "default_stream",
      &mx::default_stream,
      "device"_a,
      R"pbdoc(Get the device's default stream.)pbdoc");
  m.def(
      "set_default_stream",
      &mx::set_default_stream,
      "stream"_a,
      R"pbdoc(
        Set the default stream.

        This will make the given stream the default for the
        streams device. It will not change the default device.

        Args:
          stream (stream): Stream to make the default.
      )pbdoc");
  m.def(
      "new_stream",
      &mx::new_stream,
      "device"_a,
      R"pbdoc(Make a new stream on the given device.)pbdoc");

  nb::class_<PyStreamContext>(m, "StreamContext", R"pbdoc(
        A context manager for setting the current device and stream.

        See :func:`stream` for usage.

        Args:
            s: The stream or device to set as the default.
  )pbdoc")
      .def(nb::init<mx::StreamOrDevice>(), "s"_a)
      .def("__enter__", [](PyStreamContext& scm) { scm.enter(); })
      .def(
          "__exit__",
          [](PyStreamContext& scm,
             const std::optional<nb::type_object>& exc_type,
             const std::optional<nb::object>& exc_value,
             const std::optional<nb::object>& traceback) { scm.exit(); },
          "exc_type"_a = nb::none(),
          "exc_value"_a = nb::none(),
          "traceback"_a = nb::none());
  m.def(
      "stream",
      [](mx::StreamOrDevice s) { return PyStreamContext(s); },
      "s"_a,
      R"pbdoc(
        Create a context manager to set the default device and stream.

        Args:
            s: The :obj:`Stream` or :obj:`Device` to set as the default.

        Returns:
            A context manager that sets the default device and stream.

        Example:

        .. code-block::python

          import mlx.core as mx

          # Create a context manager for the default device and stream.
          with mx.stream(mx.cpu):
              # Operations here will use mx.cpu by default.
              pass
      )pbdoc");
  m.def(
      "synchronize",
      [](const std::optional<mx::Stream>& s) {
        s ? mx::synchronize(s.value()) : mx::synchronize();
      },
      "stream"_a = nb::none(),
      R"pbdoc(
      Synchronize with the given stream.

      Args:
        stream (Stream, optional): The stream to synchronize with. If ``None``
           then the default stream of the default device is used.
           Default: ``None``.
      )pbdoc");
}
