#ifndef CAFFE_ACC_ELTWISE_LAYER_HPP_
#define CAFFE_ACC_ELTWISE_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

/**
 * @brief Compute elementwise operations, such as product and sum,
 *        along multiple input Blobs.
 *
 * TODO(dox): thorough documentation for Forward, Backward, and proto params.
 */
template <typename Dtype>
class AccEltwiseLayer : public Layer<Dtype> {
 public:
  explicit AccEltwiseLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "AccEltwise"; }
  virtual inline int MinBottomBlobs() const { return 2; }
  virtual inline int ExactNumTopBlobs() const { return 1; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

  EltwiseParameter_EltwiseOp op_;
  vector<Dtype> coeffs_;
  Blob<int> max_idx_;

  bool stable_prod_grad_;
};

}  // namespace caffe

#endif  // CAFFE_ACC_ELTWISE_LAYER_HPP_
