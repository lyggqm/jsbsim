/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 Header:       FGThruster.h
 Author:       Jon S. Berndt
 Date started: 08/23/00

 ------------- Copyright (C) 2000  Jon S. Berndt (jsb@hal-pc.org) -------------

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place - Suite 330, Boston, MA  02111-1307, USA.

 Further information about the GNU General Public License can also be found on
 the world wide web at http://www.gnu.org.

HISTORY
--------------------------------------------------------------------------------
08/24/00  JSB  Created

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
SENTRY
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef FGTHRUSTER_H
#define FGTHRUSTER_H

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
INCLUDES
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "FGForce.h"
#include <input_output/FGXMLElement.h>
#include <input_output/FGPropertyManager.h>
#include <math/FGColumnVector3.h>
#include <string>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DEFINITIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define ID_THRUSTER "$Id: FGThruster.h,v 1.3 2005/06/13 16:59:19 ehofman Exp $"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
FORWARD DECLARATIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

namespace JSBSim {

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CLASS DOCUMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/** Base class for specific thrusting devices such as propellers, nozzles, etc.
    @author Jon Berndt
    @version $Id: FGThruster.h,v 1.3 2005/06/13 16:59:19 ehofman Exp $
    */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CLASS DECLARATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

class FGThruster : public FGForce {

public:
  /// Constructor
  FGThruster(FGFDMExec *FDMExec);
  FGThruster(FGFDMExec *FDMExec, Element *el, int num );
  /// Destructor
  virtual ~FGThruster();

  enum eType {ttNozzle, ttRotor, ttPropeller, ttDirect};

  virtual double Calculate(double tt) {
       Thrust = tt; vFn(1) = Thrust;
       return 0.0;
  }
  void SetName(string name) {Name = name;}
  virtual void SetRPM(double rpm) {};
  virtual double GetPowerRequired(void) {return 0.0;}
  virtual void SetdeltaT(double dt) {deltaT = dt;}
  double GetThrust(void) {return Thrust;}
  eType GetType(void) {return Type;}
  string GetName(void) {return Name;}
  virtual double GetRPM(void) { return 0.0; };
  double GetGearRatio(void) {return GearRatio; }
  virtual string GetThrusterLabels(int id, string delimeter);
  virtual string GetThrusterValues(int id, string delimeter);

  inline void SetThrustCoefficient(double ct) { ThrustCoeff = ct; }

protected:
  eType Type;
  string Name;
  double Thrust;
  double PowerRequired;
  double deltaT;
  double GearRatio;
  double ThrustCoeff;
  int EngineNum;
  FGPropertyManager* PropertyManager;
  virtual void Debug(int from);
};
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif
