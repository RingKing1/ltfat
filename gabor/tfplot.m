function tfplot(coef,step,yr,varargin)
%TFPLOT  Plot coefficient array on the TF plane.
%   Usage: tfplot(coef,step,yr);
%          tfplot(coef,step,yr,...);
%
%   TFPLOT(coef,step,yr) will plot a rectangular coefficient array on the
%   TF-plane. The shift in samples between each column of coefficients is
%   given by the variable step. The vector yr is a 1 x 2 vector
%   containing the lowest and highest normalized frequency.
%
%   TFPLOT is not meant to be called directly. Instead, it is called by
%   other plotting routines to give a uniform display format. 
%
%   TFPLOT (and all functions that calls it) takes the following arguments.
%
%-    'dynrange',r - Limit the dynamical range to r by using a colormap in
%                the interval [chigh-r,chigh], where chigh is the highest
%                value in the plot. The default value of [] means to not
%                limit the dynamical range.
%
%-    'db'     - Apply 20*log10 to the coefficients. This makes it possible to
%                see very weak phenomena, but it might show too much noise. A
%                logarithmic scale is more adapted to perception of sound.
%                This is the default.
%
%-    'dbsq'  - Apply 10*log10 to the coefficients. Same as the 'db'
%               option, but assume that the input is already squared.  
%
%-    'lin'   - Show the coefficients on a linear scale. This will
%               display the raw input without any modifications. Only works for
%               real-valued input.
%
%-    'linsq' - Show the square of the coefficients on a linear scale.
%
%-    'linabs'- Show the absolute value of the coefficients on a linear scale.
%
%-    'tc'    - Time centering. Move the beginning of the signal to the
%               middle of the plot. 
%
%-    'clim',[clow,chigh] - Use a colormap ranging from clow to chigh. These
%               values are passed to IMAGESC. See the help on IMAGESC.
%
%-    'image' - Use 'imagesc' to display the plot. This is the default.
%
%-    'contour' - Do a contour plot.
%          
%-    'surf'  - Do a surf plot.
%
%-    'colorbar' - Display the colorbar. This is the default.
%
%-    'nocolorbar' - Do not display the colorbar.
%
%   It is possible to customize the text by setting the following values:
%
%-    'time', t     - The word denoting time. Default is 'Time'
%
%-    'frequency',f - The word denoting frequency. Default is 'Frequency'
%  
%-    'samples',s   - The word denoting samples. Default is 'samples'
%  
%-    'normalized',n - Defult value is 'normalized'.
%  
%   See also:  sgram, plotdgt, plotdgtreal, plotwmdct, plotdwilt

%   AUTHOR : Peter Soendergaard.
%   TESTING: NA
%   REFERENCE: NA

if nargin<2
  error('%s: Too few input parameters.',upper(mfilename));
end;

definput.import={'ltfattranslate','tfplot'};
[flags,kv,fs]=ltfatarghelper({'fs','dynrange'},definput,varargin);

M=size(coef,1);
N=size(coef,2);

if size(coef,3)>1
  error('Input is multidimensional.');
end;

% Apply transformation to coefficients.
if flags.do_db
  coef=20*log10(abs(coef)+realmin);
end;

if flags.do_dbsq
  coef=10*log10(abs(coef)+realmin);
end;

if flags.do_linsq
  coef=abs(coef).^2;
end;

if flags.do_linabs
  coef=abs(coef);
end;

if flags.do_lin
  if ~isreal(coef)
    error(['Complex valued input cannot be plotted using the "lin" flag.',...
           'Please use the "linsq" or "linabs" flag.']);
  end;
end;
  
% 'dynrange' parameter is handled by thresholding the coefficients.
if ~isempty(kv.dynrange)
  maxclim=max(coef(:));
  coef(coef<maxclim-kv.dynrange)=maxclim-kv.dynrange;
end;

if flags.do_tc
  xr=(-floor(N/2):floor((N-1)/2))*step;
  coef=fftshift(coef,2);
else
  xr=(0:N-1)*step;
end;

if ~isempty(kv.fs)
  xr=xr/kv.fs;
  yr=yr*fs/2;
end;

% Convert yr to range of values
yr=linspace(yr(1),yr(2),M);

switch(flags.plottype)
  case 'image'
    if flags.do_clim
      imagesc(xr,yr,coef,kv.clim);
    else
      imagesc(xr,yr,coef);
    end;
  case 'contour'
    contour(xr,yr,coef);
  case 'surf'
    surf(xr,yr,coef);
  case 'pcolor'
    pcolor(xr,yr,coef);
end;

if flags.do_colorbar
  colorbar;
end;

axis('xy');
if ~isempty(kv.fs)
  xlabel(sprintf('%s (s)',kv.time));
  ylabel(sprintf('%s (Hz)',kv.frequency));
else
  xlabel(sprintf('%s (%s)',kv.time,kv.samples));
  ylabel(sprintf('%s (%s)',kv.frequency,kv.normalized));
end;

