#include"star.h"

void star2d::draw(figure *pfig,const matrix &A,int parity) const {
	
	map.draw(pfig,A,parity);
	
}

void star2d::drawi(figure *pfig,const matrix &A,int sr,int st,int parity) const {
	
	map.drawi(pfig,A,sr,st,parity);
	
}

void star2d::spectrum(figure *pfig,const matrix &y,int parity) const {

	map.spectrum(pfig,y,parity);
}

double star2d::luminosity() const {

	return 2*PI*(map.gl.I,(rho*nuc.eps*r*r*map.rz,map.leg.I_00))(0)*units.rho*units.r*units.r*units.r;

}

matrix star2d::N2() const {

	matrix N2;

   	N2=-eos.d*(map.gzz*(D,p)+map.gzt*(p,Dt))*((D,log(T))-(D,log(p))*eos.del_ad)-
    	eos.d*(map.gzt*(D,p)+map.gtt*(p,Dt))*((log(T),Dt)-(log(p),Dt)*eos.del_ad);
    N2=N2/rho;
    N2.setrow(0,zeros(1,nth()));

    N2=N2*units.Omega*units.Omega;
    
    return N2;
    
}

matrix star2d::Teff() const {

	matrix F;
	
	F=-opa.xi/sqrt(map.gzz)*(map.gzz*(D,T)+map.gzt*(T,Dt))/units.r*units.T;
	F=F.row(nr()-1)/SIG_SB;
	
	return pow(F,0.25);

}

matrix star2d::gsup() const {

	matrix g;
	
	g=-(map.gzz*(D,p)+map.gzt*(p,Dt))/sqrt(map.gzz)/rho;
	g=g.row(nr()-1)/units.r*units.p/units.rho;
	
	return g;

}

double star2d::virial_3P() const {

	return 6.*PI*(map.gl.I,(p*r*r*map.rz,map.leg.I_00))(0)*units.p*units.r*units.r*units.r;

}

double star2d::virial_W() const {

	return PI*(map.gl.I,(phi*rho*r*r*map.rz,map.leg.I_00))(0)*units.rho*units.phi*units.r*units.r*units.r;

}

double star2d::virial_L() const {

	return 2*PI*(map.gl.I,(rho*w*w*r*r*sin(th)*sin(th)*r*r*map.rz,map.leg.I_00))(0)*units.rho*units.phi*
		units.r*units.r*units.r;

}

double star2d::virial_ps() const {

	return -2*PI*(r.row(nr()-1)*r.row(nr()-1)*r.row(nr()-1)*ps,map.leg.I_00)(0)*units.p*units.r*units.r*units.r;
	
}

double star2d::virial() const {

	return (virial_3P()+virial_L()+virial_ps())/virial_W()+1.;

}

double star2d::energy_test() const {

	double e1,e2;
	matrix Fz;
	
	e1=luminosity();
	Fz=-opa.xi*(map.gzz*(D,T)+map.gzt*(T,Dt));
	e2=2*PI*((Fz*r*r*map.rz).row(nr()-1),map.leg.I_00)(0)*units.T*units.r;
	
	return (e1-e2)/e1;

}


matrix star2d::stream() const {

	matrix vr_,GG;
	
	vr_=rho*vr/map.rz;
	vr_=r*r*sin(th)*sin(th)*map.gzz*(D,w)+(G*r-map.rt)/map.rz*sin(th)*sin(th)*(w,Dt)+
		2*w*sin(th)/map.rz*(r*cos(th)+map.rt*sin(th))*G;
	
	vr_=r*r*map.rz/z/z*vr_;
	vr_.setrow(0,zeros(1,nth()));
	vr_=(vr_,map.leg.P_00);
	
	GG=-z*z*vr_/map.leg.l_00()/(map.leg.l_00()+1.);
	GG.setcol(0,zeros(nr(),1));
	GG=(GG,map.leg.P1_00,Dt);
	GG=GG/r;
	GG.setrow(0,zeros(1,nth()));
		
	return GG;
}

void star2d::boundary_layer() const {

	static figure fig("/XSERVE");
	matrix beta0,B4,V0,U1,U0;
	
	beta0=(map.gzz*(D,w*w)+map.gzt*(w*w,Dt))/sqrt(map.gzz);
	beta0=beta0.row(nr()-1);
	B4=(cos(th)+map.rt/r*sin(th))/(1.+map.rt*map.rt/r/r)/4./r/r/r/r/sin(th)/sin(th)/sin(th)*
		(r*r*r*r*sin(th)*sin(th)*sin(th)*sin(th)*w*w,Dt);
	B4=B4.row(nr()-1);
	V0=-r*sin(th)*(cos(th)+map.rt/r*sin(th))/sqrt(1.+map.rt*map.rt/r/r)*beta0/4./pow(B4,3./4.);
	V0=V0.row(nr()-1);
	U1=-V0/4./B4/sqrt(r*r+map.rt*map.rt)*(B4,Dt);
	U1=U1.row(nr()-1);
	U0=(rho*r*sin(th)*V0/pow(B4,0.25),map.leg.D_01)/sqrt(r*r+map.rt*map.rt)/rho/r/sin(th);
	//U0=((rho*r*sin(th),map.leg.D_10)*V0/pow(B4,0.25)/rho/r/sin(th)
	//	+(V0,map.leg.D_11)/pow(B4,0.25)
	//	-V0/4./pow(B4,5./4.)*(B4,Dt))/sqrt(r*r+map.rt*map.rt);
	U0=U0.row(nr()-1);
	
	fig.subplot(2,4);
	fig.plot(th,beta0);
	fig.label("th","beta0","");
	fig.plot(th,V0);
	fig.label("th","V0","");
	fig.plot(th,U0);
	fig.label("th","U0","");
	fig.plot(th,U1);
	fig.label("th","U1","");
	fig.plot(th,B4);
	fig.label("th","B4","");
	fig.plot(th,pow(B4,0.25));
	fig.label("th","B","");
	fig.plot(th,w.row(nr()-1));
	fig.label("th","Omega","");
	fig.plot(th,V0/pow(B4,0.25));
	fig.label("th","S","");

	matrix q1,q2;
	fig.subplot(1,2);
	q1=4./r*w*w*vr+4*(map.rt/r+cos(th)/sin(th))/r*w*w*vt+vr/map.rz*(D,w*w)+vt/r*(w*w,Dt);
	q1.setrow(0,zeros(1,nth()));
	q2=map.gzz*(D,D,w*w)+2*map.gzt*(D,w*w,Dt)+(w*w,Dt2)/r/r
	+(4./r/map.rz-map.rtt/r/r/map.rz
		+map.gzz*(-(D,w*w)/2./w/w+(D,rho)/rho-map.rzz/map.rz)
		+map.gzt*(-(w*w,Dt)/w/w+(rho,Dt)/rho+3*cos(th)/sin(th)-2.*map.rzt/map.rz)
		)*(D,w*w)
	+(3*cos(th)/sin(th)/r/r-(w*w,Dt)/2./w/w/r/r+(rho,Dt)/rho/r/r
		+map.gzt*(D,rho)/rho)*(w*w,Dt);
	q2.setrow(0,zeros(1,nth()));
	fig.colorbar();
	draw(&fig,q2);
	fig.caxis(min(q2),max(q2));
	fig.colorbar();
	draw(&fig,q1);


}
