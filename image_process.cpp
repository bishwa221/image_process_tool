#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Reading the input image
    cv::Mat inputImage = cv::imread("input_image.jpg"); // change it to your local image // use blurred image for visible sharpening effect

    // Check if the image is loaded successfully
    if (inputImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Displaying the original image
    cv::imshow("Original Image", inputImage);
    cv::waitKey(0);

    // Section 1: Sharpening, Edge Extraction (Canny), Resizing
    // Sharpen the image
    cv::Mat sharpened;
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0); // 3,3 kernel to convolve with
    cv::filter2D(inputImage, sharpened, inputImage.depth(), kernel);

    // Apply Canny edge detection
    cv::Mat edges;
    cv::cvtColor(sharpened, edges, cv::COLOR_BGR2GRAY);
    cv::Canny(edges, edges, 50, 150);

    // Resize the image by half
    cv::Mat resized;
    cv::resize(inputImage, resized, cv::Size(), 0.5, 0.5); // half the size

    // Section 2: Save the images to a file
    cv::imwrite("sharpened_image.jpg", sharpened);
    cv::imwrite("canny_edges.jpg", edges);
    cv::imwrite("resized_image.jpg", resized);

    // Section 3: Display the images in separate windows
    cv::imshow("Sharpened Image", sharpened);
    cv::imshow("Canny Edges", edges);
    cv::imshow("Resized Image", resized);
    cv::waitKey(0);

    return 0;
}
