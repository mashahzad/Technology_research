clear all;
close all;
im=imread('poutt.png');
ih=imread('pouttHost.png')
pout_histeq = histeq(im);
pout_histeq2 = histeq(ih);

figure,subplot(4,2,1),imshow(im),title('Original Image');
subplot(4,2,2),imhist(im),title('Histogram of original image')
axis([0 300 0 4000])
subplot(4,2,3),imshow(ih),title('screenshot of manipulation');
subplot(4,2,4),imhist(ih),title('Histogram of screenshot image')
axis([0 300 0 4000])
figure,subplot(4,2,5),imshow(pout_histeq),title('Org equalization Image');
subplot(4,2,6),imhist(pout_histeq),title('Histogram equalization of original image')
axis([0 300 0 4000])
figure,subplot(4,2,7),imshow(pout_histeq2),title('host Image');
subplot(4,2,8),imhist(pout_histeq2),title('Histogram equalization of host image')
axis([0 300 0 4000])