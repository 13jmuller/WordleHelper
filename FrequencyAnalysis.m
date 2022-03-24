%% Letter Analysis 
close all;
letValues = 1:26;
letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
letFreq = [975 280 475 393 1230 229 310 387 670 27 210 716 316 573 753 365 29 897 668 729 466 152 194 37 424 40];
sortedFreq = sort(letFreq, 'descend');
sortedLet = {'e', 'a', 'r', 'o', 't', 'l', 'i', 's', 'n', 'c', 'u', 'y','d', 'h','p','m', 'g','b','f', 'k', 'w','v', 'z', 'x','q', 'j'};

figure();
bar(letValues, letFreq);
set(gca,'xtick',[1:26],'xticklabel',letters);
title('Letter Frequency Analysis');
xlabel('Letters');
ylabel('Frequency');
% this is using the offical nyt guessing list
figure();
bar(letValues, sortedFreq);
set(gca,'xtick',[1:26],'xticklabel',sortedLet);
title('Letter Frequency Analysis');
xlabel('Letters');
ylabel('Frequency');

%figure();
%bar(diag(letValues), 'stacked');

%% Position Analysis 
positions = 1:5;
positionNames = {'First', 'Second', 'Third', 'Fourth', 'Fifth'};
figure();
subplot(3,2,1);
% letter e
positionE = [72 241 377 318 422];
bar(positions, positionE);
title('Position for Letter E');
ylabel('Frequency');
xlabel('Position');
set(gca,'xtick',[1:5],'xticklabel',positionNames);


% letter a
subplot(3,2,2);
positionA = [140 304 306 162 63];
bar(positions, positionA);
title('Position for Letter A');
ylabel('Frequency');
xlabel('Position');
set(gca,'xtick',[1:5],'xticklabel',positionNames);

% letter r
positionR = [105 267 163 150 212];
subplot(3,2,3);
bar(positions, positionR);
title('Position for Letter R');
ylabel('Frequency');
xlabel('Position');
set(gca,'xtick',[1:5],'xticklabel',positionNames);

% letter o
subplot(3,2,4);
positionO = [41 279 243 132 58];
bar(positions, positionO);
title('Position for Letter O');
ylabel('Frequency');
xlabel('Position');
set(gca,'xtick',[1:5],'xticklabel',positionNames);

% letter t
subplot(3,2,5);
positionT = [149 77 111 139 253];
bar(positions, positionT);
title('Position for Letter T');
ylabel('Frequency');
xlabel('Position');
set(gca,'xtick',[1:5],'xticklabel',positionNames);





