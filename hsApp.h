/***************************************************************
 * Name:      hsApp.h
 * Purpose:   Defines Application Class
 * Author:    Calmarius (calmarius@calmarius.net)
 * Created:   2012-10-21
 * Copyright: Calmarius (calmarius.net)
 * License:
 **************************************************************/

#ifndef HSAPP_H
#define HSAPP_H

#include <wx/app.h>

class hsApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // HSAPP_H
