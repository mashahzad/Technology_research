% Case Study: Urban Area Image Enhancement Using Histogram Equalization

% Read the input image (Assuming it's in grayscale for simplicity)
input_image = imread('urban_area_dawn_image.jpg');

% Check if the image is in RGB, convert to grayscale if needed
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (Urban Area at Dawn)');

% Step 1: Perform Histogram Equalization to enhance contrast
equalized_image = histeq(input_image);

% Step 2: Display the enhanced image after histogram equalization
subplot(1, 2, 2);
imshow(equalized_image);
title('Enhanced Image (After Histogram Equalization)');
