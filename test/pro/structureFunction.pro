function structureFunction,d,dt

;+
; NAME:
;      structureFunction
; PURPOSE:
;      Computes the structure function for a input time series
; CALLING SEQUENCE:
;      r=structureFunction(d,dt)
; INPUTS:
;      D=DBLARR[N]. The input time series.
;      DT=LONARR[M]. The delays to compute the structure function for
; OUTPUTS:
;      R=DBLARR[M]. The structure function evaluated at the delays.
;-

  n=n_elements(d)
  m=n_elements(dt)

  r=dblarr(m)

  for i=0,m-1 do begin
     tmp1=d[0:n-1-dt[i]]
     tmp2=d[dt[i]:n-1]
     
     dtmp=tmp1-tmp2

     r[i]=total(dtmp*dtmp)/n_elements(dtmp)
  endfor

  return,r
end
