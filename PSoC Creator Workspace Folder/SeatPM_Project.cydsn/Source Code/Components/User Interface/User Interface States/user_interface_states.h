#ifndef USER_INTERFACE_STATES_H
#define USER_INTERFACE_STATES_H
    
#include "user_interface.h"
//-----------------------------------------------------------------------------
// Generic States
void UserInterface_Initial_State(UserInterface *me, Event const *event);

//-----------------------------------------------------------------------------
// Goniometer Configuration States
void UserInterface_SetMinimumKneeAngle_State(UserInterface *me,
                                             Event const *event);
void UserInterface_SetMaximumKneeAngle_State(UserInterface *me,
                                             Event const *event);
void UserInterface_GoniometerReadingCheck_State(UserInterface *me,
                                                Event const *event);
void UserInterface_AnkleStrapRetractRelease_State(UserInterface *me,
                                                  Event const *event);

//-----------------------------------------------------------------------------
// CPM Use States
void UserInterface_ConfirmCPMStartup_State(UserInterface *me,
                                           Event const *event);
void UserInterface_ContinuousPassiveMotion_State(UserInterface *me,
                                                 Event const *event);
void UserInterface_ConfirmSpeedChange_State(UserInterface *me,
                                            Event const *event);
#endif
/* [] END OF FILE */