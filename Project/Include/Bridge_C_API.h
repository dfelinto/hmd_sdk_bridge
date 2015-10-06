#include "HMD.h"
#include "Oculus.h"

extern "C" {
	Oculus *Oculus_new(){ return new Oculus(); }
	bool Oculus_isConnected(){ return Oculus::isConnected(); }
}