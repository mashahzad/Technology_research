% Cloud Removal from Optical Satellite Imagery using CNN

% Step 1: Load Dataset
% Assume you have a dataset of cloud-covered images and corresponding cloud-free images
% For simplicity, let's assume the dataset contains images of the coastal region
% with clouds and the corresponding clean, cloud-free images

% Loading the images (here we assume the images are stored in two folders)
cloudyImagesFolder = 'path_to_cloudy_images';  % Folder containing cloud-covered images
cloudFreeImagesFolder = 'path_to_cloud_free_images';  % Folder containing cloud-free images

cloudyImages = imageDatastore(cloudyImagesFolder, 'FileExtensions', {'.jpg', '.png', '.tif'}, 'ReadFcn', @(x) imresize(imread(x), [256 256]));
cloudFreeImages = imageDatastore(cloudFreeImagesFolder, 'FileExtensions', {'.jpg', '.png', '.tif'}, 'ReadFcn', @(x) imresize(imread(x), [256 256]));

% Step 2: Prepare the Data for Training
% Convert the images to single precision for CNN training
cloudyData = augmentedImageDatastore([256 256], cloudyImages, 'ColorPreprocessing', 'gray2rgb');
cloudFreeData = augmentedImageDatastore([256 256], cloudFreeImages, 'ColorPreprocessing', 'gray2rgb');

% Step 3: Define the CNN Architecture
layers = [
    imageInputLayer([256 256 3], 'Normalization', 'none', 'Name', 'input')  % Input layer

    % Convolutional Layers
    convolution2dLayer(3, 64, 'Padding', 'same', 'Name', 'conv1')
    reluLayer('Name', 'relu1')

    convolution2dLayer(3, 128, 'Padding', 'same', 'Name', 'conv2')
    reluLayer('Name', 'relu2')

    convolution2dLayer(3, 128, 'Padding', 'same', 'Name', 'conv3')
    reluLayer('Name', 'relu3')

    convolution2dLayer(3, 64, 'Padding', 'same', 'Name', 'conv4')
    reluLayer('Name', 'relu4')

    % Output layer - predicting the clean image
    convolution2dLayer(3, 3, 'Padding', 'same', 'Name', 'output')  % Output has 3 channels (RGB)

    regressionLayer('Name', 'outputLayer')  % Regression output layer for pixel value prediction
];

% Step 4: Set Training Options
options = trainingOptions('adam', ...
    'InitialLearnRate', 0.001, ...
    'MaxEpochs', 50, ...
    'Shuffle', 'every-epoch', ...
    'ValidationFrequency', 30, ...
    'Verbose', false, ...
    'Plots', 'training-progress');

% Step 5: Train the CNN Model
% Use the `trainNetwork` function to train the CNN model
cloudRemovalModel = trainNetwork(cloudyData, cloudFreeData, layers, options);

% Step 6: Evaluate the Model (Optional)
% Load a test image for cloud removal (cloudy image) and predict the clean image
testImage = imread('path_to_test_cloudy_image.jpg');  % Test image with clouds
testImageResized = imresize(testImage, [256 256]);  % Resize to match the network input size

% Perform cloud removal using the trained model
predictedCloudFreeImage = predict(cloudRemovalModel, testImageResized);

% Display the test image and the prediction
figure;
subplot(1, 2, 1);
imshow(testImageResized);
title('Cloudy Test Image');

subplot(1, 2, 2);
imshow(predictedCloudFreeImage);
title('Predicted Cloud-Free Image');

