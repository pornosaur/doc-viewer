//
// Created by pornosaur on 10.4.19.
//

#include <opencv4/opencv2/ml.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core/types.hpp>

#include <fstream>

constexpr auto PREFIX = "./images/";

constexpr auto SVM_FILE_NAME = "SVM_trained.dat";

constexpr unsigned int CLASS_FACE = 0;

constexpr unsigned int IMG_WIDTH = 174;

constexpr unsigned int IMG_HEIGHT = 216;

constexpr int K_FOLD = 10;

constexpr float EPSILON = 1e-6;

constexpr int MAX_COUNT = 500;


std::vector<std::string> load_train_path_images(const std::string &);

void set_SVM(cv::Ptr<cv::ml::SVM> &);

void train_SVM(cv::Ptr<cv::ml::SVM> &, const cv::Mat &, const cv::Mat &);

int main(int argc, char *argv[]) {
    std::cout << "Starting..." << std::endl;

    cv::HOGDescriptor hog_des;
    hog_des.winSize = {IMG_WIDTH, IMG_HEIGHT};
    hog_des.blockSize = {8, 8};
    hog_des.blockStride = {4, 4};
    hog_des.cellSize = {4, 4};

    //auto path_images = load_train_path_images("./train.txt");

    cv::Mat gradients, labels;
    std::vector<float> descriptors;

    std::ifstream file("./train.txt");
    std::string line, num_image;

    std::cout << "\tCalculating HOG descriptors..." << std::endl;
    while (std::getline(file, line, ' ')) {
        getline(file, num_image);

        //---PREPROCESING IMG---
        cv::Mat img = cv::imread(PREFIX + line);
        cv::resize(img, img, {IMG_WIDTH, IMG_HEIGHT});           //TODO: Instead of resize, do ROI??
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        //----------------------

        //---COMPUTE HOG---
        hog_des.compute(img, descriptors);
        gradients.push_back(cv::Mat(descriptors).t());
        labels.push_back(CLASS_FACE);
        //-----------------
    }

    cv::Ptr<cv::ml::SVM> svm;
    train_SVM(svm, gradients, labels);

    std::cout << "Completed..." << std::endl;
    return 0;
}

void train_SVM(cv::Ptr<cv::ml::SVM> &svm, const cv::Mat &train_data, const cv::Mat &labels) {
    set_SVM(svm);

    std::cout << "\tTraining SVM..." << std::endl;
    cv::Ptr<cv::ml::TrainData> train_data_svm = cv::ml::TrainData::create(train_data, cv::ml::ROW_SAMPLE, labels);

    svm->trainAuto(train_data_svm, K_FOLD);

    std::cout << "\tSaving SVM model..." << std::endl;
    svm->save(SVM_FILE_NAME);
}

void set_SVM(cv::Ptr<cv::ml::SVM> &svm) {
    svm->setType(cv::ml::SVM::ONE_CLASS);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, MAX_COUNT, EPSILON));
}


std::vector<std::string> load_train_path_images(const std::string &train_path) {
    std::vector<std::string> images;

    std::ifstream fs(train_path, std::ofstream::in);

    std::string line;
    if (fs.is_open()) {
        while (fs >> line) images.emplace_back(line);
        fs.close();
    }

    return std::move(images);
}