// Copyright © 2024 Apple Inc.

#include "mlx/primitives.h"
#include "mlx/fast_primitives.h"

#define NO_CPU_MULTI(func)                                             \
  void func::eval_cpu(                                                 \
      const std::vector<array>& inputs, std::vector<array>& outputs) { \
    throw std::runtime_error(#func " has no CPU implementation.");     \
  }

#define NO_CPU(func)                                                  \
  void func::eval_cpu(const std::vector<array>& inputs, array& out) { \
    throw std::runtime_error(#func " has no CPU implementation.");    \
  }

namespace mlx::core {

NO_CPU(Abs)
NO_CPU(Add)
NO_CPU(AddMM)
NO_CPU(Arange)
NO_CPU(ArcCos)
NO_CPU(ArcCosh)
NO_CPU(ArcSin)
NO_CPU(ArcSinh)
NO_CPU(ArcTan)
NO_CPU(ArcTan2)
NO_CPU(ArcTanh)
NO_CPU(ArgPartition)
NO_CPU(ArgReduce)
NO_CPU(ArgSort)
NO_CPU(AsType)
NO_CPU(AsStrided)
NO_CPU(BitwiseBinary)
NO_CPU(BlockMaskedMM)
NO_CPU(Broadcast)
NO_CPU(Ceil)
NO_CPU(Cholesky)
NO_CPU(Concatenate)
NO_CPU(Conjugate)
NO_CPU(Convolution)
NO_CPU(Copy)
NO_CPU(Cos)
NO_CPU(Cosh)
NO_CPU_MULTI(CustomTransforms)
NO_CPU_MULTI(Depends)
NO_CPU(Divide)
NO_CPU_MULTI(DivMod)
NO_CPU(NumberOfElements)
NO_CPU(Remainder)
NO_CPU_MULTI(Eigh)
NO_CPU(Equal)
NO_CPU(Erf)
NO_CPU(ErfInv)
NO_CPU(Exp)
NO_CPU(Expm1)
NO_CPU(FFT)
NO_CPU(Floor)
NO_CPU(Full)
NO_CPU(Gather)
NO_CPU(GatherMM)
NO_CPU(GatherQMM)
NO_CPU(Greater)
NO_CPU(GreaterEqual)
NO_CPU(Hadamard)
NO_CPU(Imag)
NO_CPU(Less)
NO_CPU(LessEqual)
NO_CPU(Load)
NO_CPU(Log)
NO_CPU(Log1p)
NO_CPU(LogicalNot)
NO_CPU(LogicalAnd)
NO_CPU(LogicalOr)
NO_CPU(LogAddExp)
NO_CPU(Matmul)
NO_CPU(Maximum)
NO_CPU(Minimum)
NO_CPU(Multiply)
NO_CPU(Negative)
NO_CPU(NotEqual)
NO_CPU(Pad)
NO_CPU(Partition)
NO_CPU(Power)
NO_CPU_MULTI(QRF)
NO_CPU(QuantizedMatmul)
NO_CPU(RandomBits)
NO_CPU(Real)
NO_CPU(Reduce)
NO_CPU(Reshape)
NO_CPU(Round)
NO_CPU(Scan)
NO_CPU(Scatter)
NO_CPU(Select)
NO_CPU(Sigmoid)
NO_CPU(Sign)
NO_CPU(Sin)
NO_CPU(Sinh)
NO_CPU(Slice)
NO_CPU(SliceUpdate)
NO_CPU(Softmax)
NO_CPU(Sort)
NO_CPU_MULTI(Split)
NO_CPU(Square)
NO_CPU(Sqrt)
NO_CPU(StopGradient)
NO_CPU(Subtract)
NO_CPU_MULTI(SVD)
NO_CPU(Tan)
NO_CPU(Tanh)
NO_CPU(Transpose)
NO_CPU(Inverse)
NO_CPU(View)

namespace fast {
NO_CPU_MULTI(AffineQuantize)
} // namespace fast

} // namespace mlx::core
