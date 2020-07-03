// Created by tz301 on 2020/06/28

#include "asr/asr/model.h"

#include <string>

namespace tz_asr {

Model::Model(const std::string &pb_file,
             const std::vector<std::string> &input_nodes,
             const std::vector<std::string> &output_nodes)
    : input_nodes_(input_nodes), output_nodes_(output_nodes) {
  session_options_.config.set_use_per_session_threads(true);
  session_.reset(tensorflow::NewSession(session_options_));
  tensorflow::GraphDef graph_def;
  auto default_env = tensorflow::Env::Default();
  auto ret = tensorflow::ReadBinaryProto(default_env, pb_file, &graph_def);
  if (!ret.ok()) {
    std::string err = "Error loading " + pb_file + ": " + ret.error_message();
    throw std::invalid_argument(err);
  }
  session_->Create(graph_def);
}

kaldi::Matrix<float> Model::Infer(
    const std::vector<kaldi::Matrix<float>> &inputs) const {
  auto input_size = inputs.size();
  auto num_input_nodes = input_nodes_.size();

  if (input_size != num_input_nodes) {
    std::string err = "Error: need " + std::to_string(num_input_nodes) +
                      " inputs, only get " + std::to_string(input_size) + ".";
    throw std::invalid_argument(err);
  }

  std::vector<std::pair<std::string, tensorflow::Tensor>> tf_inputs;
  for (size_t i = 0; i < input_size; ++i) {
    tf_inputs.emplace_back(input_nodes_[i], MatrixToTensor(inputs[i]));
  }

  std::vector<tensorflow::Tensor> output;
  auto status = session_->Run(tf_inputs, output_nodes_, {}, &output);
  if (!status.ok()) {
    throw std::invalid_argument(status.error_message());
  } else {
    return TensorToMatrix(output[0]);
  }
}

tensorflow::Tensor Model::MatrixToTensor(
    const kaldi::Matrix<float> &matrix) const {
  auto rows = matrix.NumRows();
  auto cols = matrix.NumCols();
  tensorflow::TensorShape tensor_shape{rows, cols};
  tensorflow::Tensor tensor(tensorflow::DT_FLOAT, tensor_shape);
  auto float_tensor = tensor.tensor<float, 2>();

  for (decltype(rows) i = 0; i < rows; ++i) {
    for (decltype(cols) j = 0; j < cols; ++j) {
      float_tensor(i, j) = matrix(i, j);
    }
  }
  return tensor;
}

kaldi::Matrix<float> Model::TensorToMatrix(
    const tensorflow::Tensor &tensor) const {
  auto rows = tensor.shape().dim_size(0);
  auto cols = tensor.shape().dim_size(1);
  auto float_tensor = tensor.tensor<float, 2>();

  kaldi::Matrix<float> matrix(rows, cols);
  for (decltype(rows) i = 0; i < rows; ++i) {
    for (decltype(cols) j = 0; j < cols; ++j) {
      matrix(i, j) = float_tensor(i, j);
    }
  }
  return matrix;
}

}  // namespace tz_asr
