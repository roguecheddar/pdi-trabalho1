%abre uma imagem

img = imread('1.jpg');

% BW = im2bw(RGB,0.5);
% imshow(RGB), figure, imshow(BW);


%Questão 1.2
canalR = img(:,:,1); % Canal Vermelho
canalG = img(:,:,2); % Canal Verde
canalB = img(:,:,3); % Canal Azul
z = zeros(size(img, 1), size(img, 2)); %matriz de zeros
vermelho = cat(3, canalR, z, z); % Imagem vermelha
verde = cat(3, z, canalG, z); %imagem verde
azul = cat(3, z, z, canalB); %imagem azul

figure, imshow(img), title('Original')
% figure, imshow(vermelho), title('Vermelho')
% figure, imshow(verde), title('Verde')
% figure, imshow(azul), title('Azul')



%Questão 1.3
negativo = imcomplement(img);

% figure, imshow(negativo), title('Negativo')



%Questão 1.4
brilhoAdd = imadd(img, 50);

% figure, imshow(brilhoAdd), title('Brilho Aditivo')



%Questão 1.5
brilhoMult = immultiply(img, 1.5);

figure, imshow(brilhoMult), title('Brilho Multiplicativo')





% imshow(X,map), figure, imshow(BW)

% RGB = imread('1.jpg');
% 
% % image(RGB)
% 
% 
% %abre a img em rgb
% YIQ = rgb2ntsc(RGB);
% 
% image(YIQ);
% 
% I = YIQ(:,:,1);
% 
% image(I);