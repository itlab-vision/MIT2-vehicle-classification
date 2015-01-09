function imgName = MITCreateName(imgIdx, kDigits)

imgName = int2str(imgIdx);
num = imgIdx;
i = 0;
for i = 1:kDigits
    if num == 0
        break;
    end;
    num = fix(num / 10);
end

kZeros = kDigits - i + 1;
for i = 1:kZeros
    imgName = strcat('0', imgName);
end
%disp(imgName);
