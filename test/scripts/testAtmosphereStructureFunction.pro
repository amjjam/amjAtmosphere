@../pro/loadAtmosphere.pro
@../pro/structureFunction.pro

dir='~/tmp/testAtmosphere/dat/'
files='test'+strtrim(lindgen(18)/9+1,2)+strtrim((lindgen(18)/3) mod 3+1,2)+strtrim((lindgen(18) mod 3)+1,2)+'.dat'

;print,files

;stop

m=1000
offset=lindgen(1000)+1

s=dblarr(m,n_elements(files))
dt=dblarr(n_elements(files))
t0=dblarr(n_elements(files))
n=lonarr(n_elements(files))

for i=0,n_elements(files)-1 do begin
   print,files[i]
   d=loadAtmosphere(dir+files[i])
   s[*,i]=structureFunction(d.d,offset)
   dt[i]=d.dt
   t0[i]=d.t0
   n[i]=d.n
endfor

r={dt:dt,t0:t0,n:n,offset:offset,s:s}

save,filename=dir+'testAtmosphereStructureFunction.idl',r

end
