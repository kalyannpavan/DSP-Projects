% Octave Code for MXR MicroAmp Circuit

% MXR Micro Amp

clear; clc; close all;

% sampling frequency and time
Fs = 48000;
Ts = 1/Fs;

P5_value = 500e3;       %500K pot
P5_alpha = .01;     %position of pot
P5 = P5_value * P5_alpha;
R6 = 2.7e3;       %2.7k
R4 = 56e3;        %56k
R9 = 470;         %470r
R10 = 10e3;       %10k

C2 = 4.7e-11      %47pF
CR2 = Ts/(2*C2);  %Capacitor Resistance
CX2 = 0;          %Capacitor State

C3 = 4.7e-6       %4.7uF
CR3 = Ts/(2*C3);  %Capacitor Resistance
CX3 = 0;          %Capacitor State

C5 = 15e-6        %15uF
CR5 = Ts/(2*C5);  %Capacitor Resistance
CX5 = 0;          %Capacitor State


a0=((R9/R10)+1);
a1=((1/R9)+(1/CR5));
a2=(a0-(1/(R9*a1)));

b0=(1/CR3)+(1/R6);
b1=(1+(R6/P5)-(1/R6*b0));

c0=((1/CR2)+(1/R4));
c1=(1/P5)-(R6/(P5*P5*b1))+(1/CR2)+(1/R4);

d0=(1/R6+1/P5);
d1=(R6/CR3)+1-(1/(R6*d0));


% initialize input and output
Vin = [1; zeros(2047,1)];
N = length(Vin);
Vout = zeros(N,1);

for n = 1:N
  %Transfer Function
%  Vout(n)=(1/CR5*a1*a2)*(((Vin(n)*c1)/c0)-(CX3/P5*b0*b1*c0)+(CX5*CR5));
 Vout(n)=(1/(CR5*a1*a2))*(((Vin(n)*c1)/c0)-(CX3/(P5*b0*b1*c0))-(CX5*CR5)-(CX2/c0));

  %Variables needed for Capacitor State Update
  Vx=(Vout(n)*CR5*a1*a2)+(CX5*CR5);
  VinB=(Vin(n)/(P5*d0*d1))+((CX3*R6)/d1);
  VxA=Vout(n)*a0;

  %Capacitor State Update
  CX2 = (2/CR2) * (Vin(n) - Vx) - CX2;
  CX3 = (2/CR3) * (VinB) - CX3;
  CX5 = (2/CR5) * (Vx - VxA) - CX5;




end

% Perform FFT
Vout_fft = fft(Vout);

% Compute the magnitude of the frequency response
Vout_magnitude = abs(Vout_fft(1:N/2+1)); % Only keep the positive frequencies

% Compute the frequency axis
frequencies = (0:N/2) * (Fs / N);

% Plot the magnitude of the frequency response on a logarithmic scale
figure;
semilogx(frequencies, 20*log10(Vout_magnitude));
title('Frequency Response of Filter');
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
grid on;

% Customize x-axis ticks for better readability
xticks = [20, 50, 100, 200, 500, 1e3, 2e3, 5e3, 10e3, 20e3];
set(gca, 'XTick', xticks);
set(gca, 'XTickLabel', {'20', '50', '100', '200', '500', '1k', '2k', '5k', '10k', '20k'});

% Set y-axis limits
%ylim([-30 30]);

grid on;
