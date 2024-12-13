mdl_puma560
p560.plot(qz)
Ta = transl(0.6,0.1,0)*rpy2tr(0,180,0,'deg');
Tb = transl(0.4,0.6,0)*rpy2tr(0,90,0,'deg');

hold on
trplot(Ta)
trplot(Tb)

qa = p560.ikine6s(Ta)

qb = p560.ikine6s(Ta)


%p560.plot(q)

%p560.plot3d(q)

qa = p560.ikine6s(T,'r')
%p560.plot3d

ql = p560.ikine6s(T,'l')
qr = p560.ikine6s(T,'r')

p560.plot(ql)
p560.plot(qr)

tg=jtraj(qz,ql,50)
p560.plot(tg)

