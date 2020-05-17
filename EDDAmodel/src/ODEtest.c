/*
 ============================================================================
 Name        : ODEtest.c
 Author      : Andre Pieper
 Version     : V 1.0
 Copyright   : Do not copy!
 Description : ODE of a model car with seven states
 ============================================================================
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

static double t_alt;
static double t_alt2;

int func (double t, const double x[], double dx[], double *params)
{
	double lv = params[0];
	double lh = params[1];
	double m = params[2];
	double r = params[3];
	double g = params[4];
	double l = params[5];
	double rol = params[6];
	double T = params[7];
	double gamma = params[8];
	double epsilon = params[9];
	double cwA = params[10];
	double fR = params[11];
	double Jz = params[12];
	double Cv = params[13];
	double Ch = params[14];
	double u0 = params[15];
	double u1 = params[16];

	if(t<=0) {
		t_alt = t;
	}
	else if(t<t_alt) {
		t_alt = t;
	}

	double timestep = t - t_alt;
	t_alt = t;

	// ---------- Berechnung einzelner oft gebrauchten Ausdruecke ---------
	double alphav = -x[4] - lv/x[5] * x[3] + x[6];
	double alphah = -x[4] + lh/x[5] * x[3];

	double Weg = x[5] * timestep;

	double FK;

	// Berechnung der Kraefte
	if (fabs(x[6]) > 0 && fabs(Weg) > 0){
		double RH = lh / tan(x[6]);
		double rk = 1/ acos(1 - Weg*Weg / (2 * RH*RH))/ Weg;
		FK = m * x[5]*x[5]/(rk * g) * (lh/l * sin(alphav) + lv/l * sin(alphah));}
	else{
		FK = 0;
	}

	double FL = cwA * x[5]*x[5] * rol/2;
	double FR = fR * x[5];
	double Fvl = gamma * u1/(r * epsilon);
	double Fhl = (1 - gamma) * u1/(r * epsilon);
	double Fvq = Cv * (x[6] - atan(lv * x[3]/x[5]));
	double Fhq = Ch * atan(lh * x[3]/x[5]);

	dx[0] = x[5]*cos(x[2]+x[4]);
	dx[1] = x[5]*sin(x[2]+x[4]);
	dx[2] = x[3];
	dx[3] = 1 / Jz * (Fvq * lv * cos(x[6]) + Fvl * lv * sin(x[6]) - Fhq * lh);
	dx[4] = (1 / (m * x[5])) * (Fvq * cos(x[6]-x[4]) + Fvl * sin (x[6]-x[4]) + Fhq * cos(x[4]) + FK * sin(x[4]) - Fhl * sin(x[4])) - x[3];
	dx[5] = (1/m) * (Fvl * cos(x[6] - x[4]) + Fhq * sin(x[4]) + Fhl * cos(x[4]) - Fvq * sin(x[6]-x[4]) - FR - FL - FK * cos(x[4]));
	dx[6] = -x[6]/T + u0/T;

	return GSL_SUCCESS;
}

/*int jac (double t, const double x[], double *dfdy, double dfdt[], double *params)
{
	double lv = params[0];
	double lh = params[1];
	double m = params[2];
	double r = params[3];
	double g = params[4];
	double l = params[5];
	double rol = params[6];
	double T = params[7];
	double gamma = params[8];
	double epsilon = params[9];
	double cwA = params[10];
	double fR = params[11];
	double Jz = params[12];
	double Cv = params[13];
	double Ch = params[14];
	double u0 = params[15];
	double u1 = params[16];

	if(t<=0) {
		t_alt2 = t;
	}
	else if(t<t_alt2) {
		t_alt2 = t;
	}

	double timestep = t - t_alt2;
	t_alt2 = t;

	double Weg = x[5] * timestep;

	gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 7, 7);
	gsl_matrix * ma = &dfdy_mat.matrix;
	gsl_matrix_set (ma, 0, 0, 0.0);
	gsl_matrix_set (ma, 0, 1, 0.0);
	gsl_matrix_set (ma, 0, 2, -x[5]*sin(x[2] + x[4]));
	gsl_matrix_set (ma, 0, 3, 0.0);
	gsl_matrix_set (ma, 0, 4, -x[5]*sin(x[2] + x[4]));
	gsl_matrix_set (ma, 0, 5, cos(x[2] + x[4]));
	gsl_matrix_set (ma, 0, 6, 0.0);

	gsl_matrix_set (ma, 1, 0, 0.0);
	gsl_matrix_set (ma, 1, 1, 0.0);
	gsl_matrix_set (ma, 1, 2, x[5]*cos(x[2] + x[4]));
	gsl_matrix_set (ma, 1, 3, 0.0);
	gsl_matrix_set (ma, 1, 4, x[5]*cos(x[2] + x[4]));
	gsl_matrix_set (ma, 1, 5, sin(x[2] + x[4]));
	gsl_matrix_set (ma, 1, 6, 0.0);

	gsl_matrix_set (ma, 2, 0, 0.0);
	gsl_matrix_set (ma, 2, 1, 0.0);
	gsl_matrix_set (ma, 2, 2, 0.0);
	gsl_matrix_set (ma, 2, 3, 1.0);
	gsl_matrix_set (ma, 2, 4, 0.0);
	gsl_matrix_set (ma, 2, 5, 0.0);
	gsl_matrix_set (ma, 2, 6, 0.0);

	gsl_matrix_set (ma, 3, 0, 0.0);
	gsl_matrix_set (ma, 3, 1, 0.0);
	gsl_matrix_set (ma, 3, 2, 0.0);
	gsl_matrix_set (ma, 3, 3, -((Ch*(lh*lh))/(x[5]*(((lh*lh)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Cv*(lv*lv)*cos(x[6]))/(x[5]*(((lv*lv)*(x[3]*x[3]))/(x[5]*x[5]) + 1)))/Jz);
	gsl_matrix_set (ma, 3, 4, 0.0);
	gsl_matrix_set (ma, 3, 5, ((Ch*(lh*lh)*x[3])/((x[5]*x[5])*(((lh*lh)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Cv*(lv*lv)*x[3]*cos(x[6]))/((x[5]*x[5])*(((lv*lv)*(x[3]*x[3]))/(x[5]*x[5]) + 1)))/Jz);
	gsl_matrix_set (ma, 3, 6, (Cv*lv*cos(x[6]) - Cv*lv*sin(x[6])*(x[6] - atan((lv*x[3])/x[5])) + (gamma*lv*u1*cos(x[6]))/(epsilon*r))/Jz);

	gsl_matrix_set (ma, 4, 0, 0.0);
	gsl_matrix_set (ma, 4, 1, 0.0);
	gsl_matrix_set (ma, 4, 2, 0.0);
	gsl_matrix_set (ma, 4, 3, - ((Cv*lv*cos(x[4] - x[6]))/(x[5]*(((lv*lv)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) - (Ch*lh*cos(x[4]))/(x[5]*(((lh*lh)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Weg*m*(x[5]*x[5])*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*lv*cos(x[4] - x[6] + (lv*x[3])/x[5]))/(l*x[5]) - (lh*lv*cos(x[4] - (lh*x[3])/x[5]))/(l*x[5])))/g)/(m*x[5]) - 1);
	gsl_matrix_set (ma, 4, 4, -(Ch*atan((lh*x[3])/x[5])*sin(x[4]) + Cv*sin(x[4] - x[6])*(x[6] - atan((lv*x[3])/x[5])) - (u1*cos(x[4])*(gamma - 1))/(epsilon*r) + (gamma*u1*cos(x[4] - x[6]))/(epsilon*r) + (Weg*m*(x[5]*x[5])*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*cos(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*cos(x[4] - (lh*x[3])/x[5]))/l))/g + (Weg*m*(x[5]*x[5])*cos(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l))/g)/(m*x[5]));
	gsl_matrix_set (ma, 4, 5,((Cv*lv*x[3]*cos(x[4] - x[6]))/((x[5]*x[5])*(((lv*lv)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) - (Ch*lh*x[3]*cos(x[4]))/((x[5]*x[5])*(((lh*lh)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Weg*m*(x[5]*x[5])*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*lv*x[3]*cos(x[4] - x[6] + (lv*x[3])/x[5]))/(l*(x[5]*x[5])) - (lh*lv*x[3]*cos(x[4] - (lh*x[3])/x[5]))/(l*(x[5]*x[5]))))/g - (2*Weg*m*x[5]*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l))/g)/(m*x[5]) - (Cv*cos(x[4] - x[6])*(x[6] - atan((lv*x[3])/x[5])) + Ch*atan((lh*x[3])/x[5])*cos(x[4]) + (u1*sin(x[4])*(gamma - 1))/(epsilon*r) - (gamma*u1*sin(x[4] - x[6]))/(epsilon*r) - (Weg*m*(x[5]*x[5])*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l))/g)/(m*(x[5]*x[5])));
	gsl_matrix_set (ma, 4, 6, (Cv*cos(x[4] - x[6]) + Cv*sin(x[4] - x[6])*(x[6] - atan((lv*x[3])/x[5])) + (gamma*u1*cos(x[4] - x[6]))/(epsilon*r) + (Weg*lh*m*(x[5]*x[5])*cos(x[4] - x[6] + (lv*x[3])/x[5])*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh))))/(g*l) - ((Weg*Weg*Weg)*m*(x[5]*x[5])*sin(x[4])*tan(x[6])*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l)*((tan(x[6])*tan(x[6])) + 1))/(g*(lh*lh)*sqrt(1 - (((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)) - 1)*(((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)) - 1))))/(m*x[5]));

	gsl_matrix_set (ma, 5, 0, 0.0);
	gsl_matrix_set (ma, 5, 1, 0.0);
	gsl_matrix_set (ma, 5, 2, 0.0);
	gsl_matrix_set (ma, 5, 3, ((Ch*lh*sin(x[4]))/(x[5]*(((lh*lh)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) - (Cv*lv*sin(x[4] - x[6]))/(x[5]*(((lv*lv)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Weg*m*(x[5]*x[5])*cos(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*lv*cos(x[4] - x[6] + (lv*x[3])/x[5]))/(l*x[5]) - (lh*lv*cos(x[4] - (lh*x[3])/x[5]))/(l*x[5])))/g)/m);
	gsl_matrix_set (ma, 5, 4, (Cv*cos(x[4] - x[6])*(x[6] - atan((lv*x[3])/x[5])) + Ch*atan((lh*x[3])/x[5])*cos(x[4]) + (u1*sin(x[4])*(gamma - 1))/(epsilon*r) - (gamma*u1*sin(x[4] - x[6]))/(epsilon*r) + (Weg*m*(x[5]*x[5])*cos(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*cos(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*cos(x[4] - (lh*x[3])/x[5]))/l))/g - (Weg*m*(x[5]*x[5])*sin(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l))/g)/m);
	gsl_matrix_set (ma, 5, 5, -(fR + cwA*rol*x[5] - (Cv*lv*x[3]*sin(x[4] - x[6]))/((x[5]*x[5])*(((lv*lv)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Ch*lh*x[3]*sin(x[4]))/((x[5]*x[5])*(((lh*lh)*(x[3]*x[3]))/(x[5]*x[5]) + 1)) + (Weg*m*(x[5]*x[5])*cos(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*lv*x[3]*cos(x[4] - x[6] + (lv*x[3])/x[5]))/(l*(x[5]*x[5])) - (lh*lv*x[3]*cos(x[4] - (lh*x[3])/x[5]))/(l*(x[5]*x[5]))))/g - (2*Weg*m*x[5]*cos(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)))*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l))/g)/m);
	gsl_matrix_set (ma, 5, 6, (Cv*sin(x[4] - x[6]) - Cv*cos(x[4] - x[6])*(x[6] - atan((lv*x[3])/x[5])) + (gamma*u1*sin(x[4] - x[6]))/(epsilon*r) - (Weg*lh*m*(x[5]*x[5])*cos(x[4] - x[6] + (lv*x[3])/x[5])*cos(x[4])*acos(1 - ((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh))))/(g*l) + ((Weg*Weg*Weg)*m*(x[5]*x[5])*cos(x[4])*tan(x[6])*((lh*sin(x[4] - x[6] + (lv*x[3])/x[5]))/l + (lv*sin(x[4] - (lh*x[3])/x[5]))/l)*((tan(x[6])*tan(x[6])) + 1))/(g*(lh*lh)*sqrt(1 - (((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)) - 1)*(((Weg*Weg)*(tan(x[6])*tan(x[6])))/(2*(lh*lh)) - 1))))/m);

	gsl_matrix_set (ma, 6, 0, 0.0);
	gsl_matrix_set (ma, 6, 1, 0.0);
	gsl_matrix_set (ma, 6, 2, 0.0);
	gsl_matrix_set (ma, 6, 3, 0.0);
	gsl_matrix_set (ma, 6, 4, 0.0);
	gsl_matrix_set (ma, 6, 5, 0.0);
	gsl_matrix_set (ma, 6, 6, -1/T);

	dfdt[0] = 0.0;
	dfdt[1] = 0.0;
	dfdt[2] = 0.0;
	dfdt[3] = 0.0;
	dfdt[4] = 0.0;
	dfdt[5] = 0.0;
	dfdt[6] = 0.0;

	return GSL_SUCCESS;
}*/

int main (void)
{
	// ------------------------------ Parameter -----------------
	// Gegeben
	double lv =  0.1285;      	// Laenge vordere Haelfte [m]
	double lh =  0.1285;      	// Laenge hintere Haelfte [m]
	double m = 2.0;           	// Gewicht [Kg] 2
	double r = 0.0335;        	// Radradius [m]
	double g = 9.80665;       	// Erdbeschleunigung [m/s^2]
	double l = lv+lh;       	// Gesamtlaenge des Radstandes [m]
	double rol = 1.2041;      	// Luftdichte (Meeresspiegel, 20 Grad Celsius) [kg/m^3]
	double T = 0.01;          	// zeitliche Verzoegerung des Inputs [s]
	// Gesucht
	double gamma = 0.5;      	// Uebersetzungsfaktor Kraftverteilung Vorder- und Hinterrad [-]
	double epsilon = 5.52;   	// Uebersetzungsfaktor Motor zu Raeder vorne und hinten [-]
	double cwA = 1.15*0.025944; // Stroemungswiderstandskoeffizient mal Flaeche [-]*[m^2]
	double fR = 4*0.45;      	// Reibungskoeffizient [-]
	double Jz = 0.0149*m; 		//Traegheitsmoment [Kg * m^2]
	double Cv = 1.0;           	// Schraeglaufuebersetzung vorne [-]
	double Ch = 0.9;         	// Schraeglaufuebersetzung hinten [-]
	// Input
	double u0 = 0.3;       		// Auslenkwinkel (maximal +-0.35) [-] 0.2
	double u1 = 0.05;

	double params[17] = {lv, lh, m, r, g, l, rol, T, gamma, epsilon, cwA, fR, Jz, Cv, Ch, u0, u1};

	double h = 1e-6;
	const gsl_odeiv2_step_type * Tt  = gsl_odeiv2_step_rk8pd;
	gsl_odeiv2_step * s  = gsl_odeiv2_step_alloc (Tt, 7);
	gsl_odeiv2_control * c  = gsl_odeiv2_control_y_new (1e-3, 0.0);
	gsl_odeiv2_evolve * e  = gsl_odeiv2_evolve_alloc (7);

	gsl_odeiv2_system sys = {func, NULL, 7, &params};

	struct timeval tv_start;
	struct timeval tv_end;
	unsigned long time_in_micros = 0;
	int i;

	for (i=0;i<10000;i++){
		double t = 0.0;
		double t_end = 1.0;
		double y[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};

		gettimeofday(&tv_start,NULL);	// Start der Zeitmessung

		//int i = 0;

		while(t < t_end)
		{
			int status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &t, t_end, &h, y);

			if (status != GSL_SUCCESS)
			{
				printf ("error, return value=%d\n", status);
				break;
			}

			//printf ("%.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f\n", t, y[0], y[1], y[2], y[3], y[4], y[5], y[6]);

			//i++;
		}

		gettimeofday(&tv_end,NULL);
		time_in_micros += (1000000 * tv_end.tv_sec + tv_end.tv_usec) - (1000000 * tv_start.tv_sec + tv_start.tv_usec);
	}
	printf ("Die Berechnung lief %.7f Sekunden mit ... Solver-Aufrufen.\n", (double)time_in_micros/1000000/10000);

	gsl_odeiv2_evolve_free (e);
	gsl_odeiv2_control_free (c);
	gsl_odeiv2_step_free (s);
	return 0;
}
