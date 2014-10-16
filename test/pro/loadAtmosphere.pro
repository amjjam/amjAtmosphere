function loadAtmosphere,filename

;+
; NAME:
;      loadAtmosphere
; PURPOSE:
;      Loads a file created by testAtmosphere
; CALLING SEQUENCE:
;      d=loadAtmosphere(filename)
; INPUTS:
;      FILENAME=STRING. Name of file to load
; OUTPUTS:
;      d={dt=double. Time between data points,
;         tau=double. Coherence time.
;         d=DBLARR[N]. The delays.
;        }
;-

  openr,un,filename,/get_lun,/compress

  n=0l & dt=0d & t0=0d
  readu,un,n,dt,t0

  d=dblarr(n)
  readu,un,d

  free_lun,un

  return,{n:n,dt:dt,t0:t0,d:d}
end

  
