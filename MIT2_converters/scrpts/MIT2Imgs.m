function [] = MIT2Imgs(matInp, path)
data = load(matInp);

disp('--------------------------------------------------------------');
disp('train_carvan:');
disp(length(data.train_carvan));
train_carvan_path = strcat(path, '\train_carvan');
file_train_carvan = strcat(train_carvan_path, '\file_train_carvan.txt');
disp(file_train_carvan);
f = fopen(file_train_carvan, 'w');
for i = 1:length(data.train_carvan)
    imgName = MITCreateName(i, 4);
    lbl = data.train_carvan(1, i).lbl;
    fprintf(f, strcat(imgName, '\t'));
    if lbl == 0
        fprintf(f, 'car');
    else
        fprintf(f, 'van');
    end
    fprintf(f, '\t');
    img = data.train_carvan(1, i).im;    
    imwrite(img, strcat(strcat(train_carvan_path, '\train_carvan_img\'), strcat(imgName, '.bmp')), 'bmp');
    msk = data.train_carvan(1, i).mask;
    imwrite(msk, strcat(strcat(train_carvan_path, '\train_carvan_msk\'), strcat(imgName, '.bmp')), 'bmp');
    bbox = data.train_carvan(1, i).bdgbox;    
    fprintf(f, strcat(int2str(bbox.colstart), '\t')); %x1
    fprintf(f, strcat(int2str(bbox.rowstart), '\t')); %y1
    fprintf(f, strcat(int2str(bbox.colend), '\t'));   %x2
    fprintf(f, strcat(int2str(bbox.rowend), '\n'));   %y2 
end
fclose(f);

disp('--------------------------------------------------------------');
disp('test_carvan:');
disp(length(data.test_carvan));
test_carvan_path = strcat(path, '\test_carvan');
file_test_carvan = strcat(test_carvan_path, '\file_test_carvan.txt');
disp(file_test_carvan);
f = fopen(file_test_carvan, 'w');
for i = 1:length(data.test_carvan)
    imgName = MITCreateName(i, 4);
    lbl = data.test_carvan(1, i).lbl;
    fprintf(f, strcat(imgName, '\t'));
    if lbl == 0
        fprintf(f, 'car');
    else
        fprintf(f, 'van');
    end
    fprintf(f, '\t');
    img = data.test_carvan(1, i).im;
    imwrite(img, strcat(strcat(test_carvan_path, '\test_carvan_img\'), strcat(imgName, '.bmp')), 'bmp');
    msk = data.test_carvan(1, i).mask;
    imwrite(msk, strcat(strcat(test_carvan_path, '\test_carvan_msk\'), strcat(imgName, '.bmp')), 'bmp');
    bbox = data.test_carvan(1, i).bdgbox;
    fprintf(f, strcat(int2str(bbox.colstart), '\t')); %x1
    fprintf(f, strcat(int2str(bbox.rowstart), '\t')); %y1
    fprintf(f, strcat(int2str(bbox.colend), '\t'));   %x2
    fprintf(f, strcat(int2str(bbox.rowend), '\n'));   %y2 
end
fclose(f);

disp('--------------------------------------------------------------');
disp('train_sedantaxi:');
disp(length(data.train_sedantaxi));
train_sedantaxi_path = strcat(path, '\train_sedantaxi');
file_train_sedantaxi = strcat(train_sedantaxi_path, '\file_train_sedantaxi.txt');
disp(file_train_sedantaxi);
f = fopen(file_train_sedantaxi, 'w');
for i = 1:length(data.train_sedantaxi)
    imgName = MITCreateName(i, 4);
    lbl = data.train_sedantaxi(1, i).lbl;
    fprintf(f, strcat(imgName, '\t'));
    if lbl == 0
        fprintf(f, 'sedan');
    else
        fprintf(f, 'taxi');
    end
    fprintf(f, '\t');
    img = data.train_sedantaxi(1, i).im;
    imwrite(img, strcat(strcat(train_sedantaxi_path, '\train_sedantaxi_img\'), strcat(imgName, '.bmp')), 'bmp');
    msk = data.train_sedantaxi(1, i).mask;
    imwrite(msk, strcat(strcat(train_sedantaxi_path, '\train_sedantaxi_msk\'), strcat(imgName, '.bmp')), 'bmp');
    bbox = data.train_sedantaxi(1, i).bdgbox;
    fprintf(f, strcat(int2str(bbox.colstart), '\t')); %x1
    fprintf(f, strcat(int2str(bbox.rowstart), '\t')); %y1
    fprintf(f, strcat(int2str(bbox.colend), '\t'));   %x2
    fprintf(f, strcat(int2str(bbox.rowend), '\n'));   %y2     
end
fclose(f);

disp('--------------------------------------------------------------');
disp('test_sedantaxi:');
disp(length(data.test_sedantaxi));
test_sedantaxi_path = strcat(path, '\test_sedantaxi');
file_test_sedantaxi = strcat(test_sedantaxi_path, '\file_test_sedantaxi.txt');
disp(file_test_sedantaxi);
f = fopen(file_test_sedantaxi, 'w');
for i = 1:length(data.test_sedantaxi)
    imgName = MITCreateName(i, 4);
    lbl = data.test_sedantaxi(1, i).lbl;
    fprintf(f, strcat(imgName, '\t'));
    if lbl == 0
        fprintf(f, 'sedan');
    else
        fprintf(f, 'taxi');
    end
    fprintf(f, '\t');
    img = data.test_sedantaxi(1, i).im;
    imwrite(img, strcat(strcat(test_sedantaxi_path, '\test_sedantaxi_img\'), strcat(imgName, '.bmp')), 'bmp');
    msk = data.test_sedantaxi(1, i).mask;
    imwrite(msk, strcat(strcat(test_sedantaxi_path, '\test_sedantaxi_msk\'), strcat(imgName, '.bmp')), 'bmp');
    bbox = data.test_sedantaxi(1, i).bdgbox;
    fprintf(f, strcat(int2str(bbox.colstart), '\t')); %x1
    fprintf(f, strcat(int2str(bbox.rowstart), '\t')); %y1
    fprintf(f, strcat(int2str(bbox.colend), '\t'));   %x2
    fprintf(f, strcat(int2str(bbox.rowend), '\n'));   %y2 
end
fclose(f);
