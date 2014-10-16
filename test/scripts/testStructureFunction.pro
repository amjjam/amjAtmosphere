restore,'~/tmp/testAtmosphere/dat/testAtmosphereStructureFunction.idl'

set_plot,'ps'
!p.font=1

device,filename='../afigures/all.eps',xsize=6,ysize=4,/inches,/encapsulated

plot,r.offset*r.dt[0],r.s[*,0],/xlog,/ylog,$
     xtitle='Delay (ms)',ytitle='Structure function (microns!U2!N)'

for i=1,n_elements(r.dt)-1 do oplot,r.offset*r.dt[i],r.s[*,i]

device,/close

;
;
;

t0=r.t0[sort(r.t0)]
t0=t0[uniq(t0)]

device,filename='../afigures/all2.eps',xsize=6,ysize=4,/inches,/encapsulated,$
       /color

rr=[0,255,0,0]
gg=[0,0,255,0]
bb=[0,0,0,255]

tvlct,rr,gg,bb

p=r
p.s=r.s/0.5^2*(2*!pi)^2
fac=1.0

plot,p.offset*p.dt[0],p.s[*,0]*fac,/xlog,/ylog,$
     xtitle='Delay (ms)',ytitle='Structure function (radians!U2!N)',/nodata;,$
;     xrange=[1,100],yrange=[0.9,1.2],/ystyle

for i=0,n_elements(p.dt)-1 do begin
   j=where(t0 eq p.t0[i])
   print,j
   oplot,p.offset*p.dt[i],p.s[*,i]*fac,color=j+1
endfor

oplot,[0.1,1e3],[1,1],linestyle=1

oplot,[3,3],[1e-10,1e10],linestyle=1
oplot,[10,10],[1e-10,1e10],linestyle=1
oplot,[30,30],[1e-10,1e10],linestyle=1

device,/close

;
; Fit power law to all structure functions combined
;

x=alog(p.offset*p.dt[0])
for i=1,n_elements(p.dt)-1 do x=[x,alog(p.offset*p.dt[i])]
y=alog(p.s[*,0]*p.t0[0]^(5./3.))
for i=1,n_elements(p.dt)-1 do y=[y,alog(p.s[*,i]*p.t0[i]^(5./3.))]

result=linfit(x,y,sigma=sigma)



end
