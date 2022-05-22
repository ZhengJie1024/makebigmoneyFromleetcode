
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>

#define CHECK(CONDITION)

class Initer {
public:
  explicit Initer() {}
  virtual void InitParams(std::vector<std::vector<float>>& weight) = 0;
};

class NormIniter : public Initer{
public:
  void InitParams(std::vector<std::vector<float>>& weights) {
    std::srand( (unsigned)time( NULL ) );
    for (auto& weight: weights) {
      for (int i = 0; i < weight.size(); i++) {
        weight[i] += rand() / 32767.0;
      }
    }
  }
};

class Layer {
public:
  explicit Layer(Initer* initer, std::string name, int input_size , int ouput_size) : initer_(initer), name_(name), input_size_(input_size), ouput_size_(ouput_size){}
  // 前向计算
  virtual void Compute(std::vector<std::vector<float >> &input,
      std::vector<std::vector<float >> &ouput) = 0;

  // 后项计算
  virtual void ComputeGradient() = 0;

  virtual void InitParams() = 0;

  ~ Layer() {
    delete initer_;
    std::cout << " del initer_ in Layer";
  }

protected:
  std::string name_;
  std::vector<std::vector<float>> weight_;
  Initer* initer_;
  int input_size_;
  int ouput_size_;
};

class MlpLayer: public Layer {
public:
    explicit MlpLayer(Initer* initer, std::string name, int input_size , int ouput_size) : Layer(initer, name, input_size, ouput_size) {
    }

    void Compute(std::vector<std::vector<float >> &input,
                 std::vector<std::vector<float >> &ouput) override {
      // input [-1, input_size] ,  ouput [-1, ouput_size]
      // weight_ [input_size, ouput_size_]

    }

    void ComputeGradient() override {

    }

    void InitParams() override {
      weight_.resize(input_size_, std::vector<float> (ouput_size_, 0.0));
      initer_->InitParams(weight_);
    };
};

class LossFunction{
public:
  explicit LossFunction() {}

  virtual void ComputeLoss(std::vector<std::vector<float >> &input, std::vector<float > lable) = 0;
  virtual void ComputeGradient() = 0;
};

class BinaryClassLossFunction : public LossFunction {
public:
  void ComputeLoss(std::vector<std::vector<float >> &input, std::vector<float > lable) override {

  }

  void ComputeGradient() override {

  }
};

class LrNetWork {
public:
  explicit LrNetWork() {

    Initer* normer = new NormIniter();
    auto layer = new MlpLayer(normer, "layer1", 1, 10);
    layers_.push_back(layer);
  }

  ~ LrNetWork() {
    for (auto layer:layers_) {
      delete layer;
    }
    layers_.clear();
    std::cout << " del layers_ in LrNetWork";
    delete loss_;
    std::cout << " del LossFunction in LrNetWork";
  }

  void ComputeLoss() {

  }

private:
  std::vector<Layer*> layers_;
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

