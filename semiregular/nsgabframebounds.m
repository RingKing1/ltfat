function [AF,BF]=nsgabframebounds(g,a,Ls)
%NSGABFRAMEBOUNDS  Frame bounds of nonstationnary Gabor frame
%   Usage:  fcond=nsgabframebounds(g,a,Ls);
%           [A,B]=nsgabframebounds(g,a,Ls);
%
%   Input parameters:
%         g     : Cell array of windows
%         a     : Vector of time positions of windows.
%         Ls    : Length of analyzed signal.
%   Output parameters:
%         fcond : Frame condition number (B/A)
%         A,B   : Frame bounds.
%
%   NSGABFRAMEBOUNDS(g,a,Ls) calculates the ratio B/A of the frame bounds of
%   the nonstationary discrete Gabor frame defined by windows given in g at
%   positions given by a. Please see the help on NSDGT for a more thourough
%   description of g and _a.
%
%   [A,B]=NSGABFRAMEBOUNDS(g,a,Ls) calculates the frame bounds A and B.
%
%   The computed frame bounds are only valid for the 'painless case' when
%   the number of frequency channels used for computation of NSDGT is greater
%   than or equal to the window length. This correspond to cases for which
%   the frame operator is diagonal.
%
%   See also:  nsgabtight, nsdgt, insdgt
%
%R  ltfatnote010
  
%   AUTHOR : Florent Jaillet
%   TESTING: TEST_NSDGT
%   REFERENCE:

timepos=cumsum(a)-a(1);

N=length(a); % Number of time positions
f=zeros(Ls,1); % Diagonal of the frame operator

% Compute the diagonal of the frame operator:
% sum up in time (overlap-add) all the contributions of the windows as if 
% we where using windows in g as analysis and synthesis windows
for ii=1:N
  shift=floor(length(g{ii})/2);
  temp=abs(circshift(g{ii},shift)).^2*length(g{ii});
  tempind=mod((1:length(g{ii}))+timepos(ii)-shift-1,Ls)+1;
  f(tempind)=f(tempind)+temp;
end

% Initialize the result with g
gd=g;

% Correct each window to ensure perfect reconstrution
for ii=1:N
  shift=floor(length(g{ii})/2);
  tempind=mod((1:length(g{ii}))+timepos(ii)-shift-1,Ls)+1;
  gd{ii}(:)=circshift(circshift(g{ii},shift)./f(tempind),-shift);
end

AF=min(f);
BF=max(f);

if nargout<2
  % Avoid the potential warning about division by zero.
  if AF==0
    AF=Inf;
  else
    AF=BF/AF;
  end;
end;