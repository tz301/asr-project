// Created by tz301 on 2020/06/28

#ifndef ASR_ASR_MODEL_H_
#define ASR_ASR_MODEL_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "matrix/kaldi-matrix.h"
#include "tensorflow/cc/saved_model/loader.h"

namespace tz_asr {

/**
 * @brief Model.
 */
class Model {
 public:
  /**
   * @brief Construct a new Model object.
   * @param pb_file pb file.
   * @param input_nodes input node names.
   * @param output_nodes output node names.
   */
  Model(const std::string &pb_file, const std::vector<std::string> &input_nodes,
        const std::vector<std::string> &output_nodes);

  /**
   * @brief Inference.
   * @param inputs mfcc and ivector feature matrix.
   * @return acoustic prob matrix.
   */
  kaldi::Matrix<float> Infer(
      const std::vector<kaldi::Matrix<float>> &inputs) const;

 private:
  /**
   * @brief Convert matrix to tensor.
   * @param matrix matrix.
   * @return tensor.
   */
  tensorflow::Tensor MatrixToTensor(const kaldi::Matrix<float> &matrix) const;

  /**
   * @brief Convert tensor to matrix.
   * @param tensor tensor.
   * @return matrix.
   */
  kaldi::Matrix<float> TensorToMatrix(const tensorflow::Tensor &tensor) const;

  const std::vector<std::string> input_nodes_;    // Input node names.
  const std::vector<std::string> output_nodes_;   // Output node names.
  std::unique_ptr<tensorflow::Session> session_;  // tensorflow session.
  tensorflow::SessionOptions session_options_;    // Session options.
};

}  // namespace tz_asr

#endif  // ASR_ASR_MODEL_H_
