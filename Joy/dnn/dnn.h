
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>

#define CHECK(CONDITION)

typedef unsigned long uint64; // 8 字节

class Initer {
public:
  explicit Initer() {}
  virtual void InitParams(std::vector<std::vector<float>>& weight) = 0;
};

class NormIniter : public Initer{
public:
  void InitParams(float& weight) {
    std::srand((unsigned)time(NULL));
    weight = (rand() % 1024) / 1024.0 - 0.5;
  }
};

class Layer {
public:
  explicit Layer(std::string name, int input_size , int ouput_size) : name_(name), input_size_(input_size), ouput_size_(ouput_size){}
  // 前向计算
  virtual void Compute(std::vector<float> &input,
                       std::vector<float> &ouput) = 0;

  // 后项计算
  virtual void ComputeGradient() = 0;

  virtual void InitParams() = 0;

  ~ Layer() {
    std::cout << " del initer_ in Layer ";
  }

protected:
  std::string name_;
  int input_size_;
  int ouput_size_;
};

class LossFunction{
public:
  explicit LossFunction() {}

  virtual void ComputeLoss(const std::vector<float > &input,
                           const std::vector<float > &lable,
                           std::vector<float > &loss) = 0;
  virtual void ComputeGradient(const std::vector<float > &input,
                               const std::vector<float > &lable,
                               std::vector<float > &gradient) = 0;
};

class BinaryClassLossFunction : public LossFunction {
public:
  void ComputeLoss(const std::vector<float > &input,
                   const std::vector<float > &lable,
                   std::vector<float > &loss) override {
    // inputs = logit
    loss.clear();
    float p = 1 / (exp(- input[0]) + 1);
    loss[0] = - (lable[0] * log(p) + (1 - lable[0]) * log(1 - p));
  }

  void ComputeGradient(const std::vector<float > &input,
                       const std::vector<float > &lable,
                       std::vector<float > &gradient) override {
    // gradient dim = input dim
    float p = 1 / (exp(- input[0]) + 1);
    gradient[0] = (p - lable[0]);
  }
};



class EmbeddingMap {
public:
  void GetEmbedding(int slot, int feature, std::vector<float>& embedding) {
    return;
  }

  void GetWeight(int slot, int feature, float& weight) {

  }

  uint64 GetSign() {

  }
};

class FMModel {
public:
  explicit FMModel() {
  }

  ~ FMModel() {
    for (auto layer:layers_) {
      delete layer;
    }
    layers_.clear();
    std::cout << " del layers_ in LrNetWork";
    delete loss_;
    std::cout << " del LossFunction in LrNetWork";
  }

  void ComputeLoss(std::vector<int>& features) {
    std::vector<std::vector<float>> embeddings(features.size());
    int slot = 0;
    for (int i = 0; i < features.size() ; i++) {
      slot += 1;
      auto& embedding = embeddings[i];
      embedding_maper_.GetEmbedding(slot, features[i], embedding);
    }

    // 一阶
    std::vector<float> weights(features.size(), 0);
    for (int i = 0; i < features.size() ; i++) {
      slot += 1;
      embedding_maper_.GetWeight(slot, features[i], weights[i]);
    }

    // 二阶段
    // embedding -> input1(dim = 256) -> (cmt1) -> output1(dim = 128) -> (cmt2) -> output2(dim = 1) -> (loss cmt) -> loss
    // loss -> (cmt gradient(label , input))
    //    -> g1 -> (cmt2 gradient 2 (g1, output1) -> (g2, weight gradient))
    //    -> g2 -> (cmt1 gradient 1 (g2, input1) -> g3, weight gradient )
    //    -> g3 -> 更新对应位子的embedding
  }

private:
  std::vector<Layer*> layers_;
  EmbeddingMap embedding_maper_;
  LossFunction* loss_;
};

class DataSet {
public:
  void GetBatch(int batch_size, std::vector<std::vector<float>>& features, std::vector<float>& labels) {
    std::srand((unsigned)time( NULL ) );
    labels.clear();
    features.clear();
    for (int i = 0; i < batch_size; i++) {
      auto randData = rand();

      int ground_true = randData % MAX;
      labels.push_back(ground_true % 2);
      features.emplace_back();
      features.back().push_back(ground_true % 2);
    }
  }

private:
    int MAX = 100;
};

