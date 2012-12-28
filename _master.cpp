/*
Copyright (c) 2012, Dávid Csirmaz
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Global constants

const double PI = 3.1415926536;
const double RIGHT_ANGLE = PI / 2.0;

const double RED_N = 1.3073;
const double GREEN_N = 1.3114;
const double BLUE_N = 1.3145;


// Standard files

#include <cstdio>
#include <cmath>
#include <limits>
#include <cstdarg>
#include <stdint.h>

#include <vector>
#include <algorithm>
#include <map>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/scrolwin.h>

// C++ header files

#include <wx/msgdlg.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/thread.h>

#include "vector.h"
#include "matrix.h"
#include "mesh.h"
#include "hsApp.h"
#include "CrystalCompositionEditorDialog.h"
#include "hsMain.h"
#include "HaloRenderingThread.h"
#include "CrystalEditorFrame.h"
#include "HexagonalPrismGeneratorDialog.h"
#include "utils.h"
#include "logging.h"
#include "AddCrystalToDisplayDialog.h"
#include "RenderSetupDialog.h"
#include "RenderingProcessFrame.h"

// Sources

#include "mesh.cpp"
#include "hsApp.cpp"
#include "hsMain.cpp"
#include "CrystalEditorFrame.cpp"
#include "HexagonalPrismGeneratorDialog.cpp"
#include "utils.cpp"
#include "vector.cpp"
#include "matrix.cpp"
#include "logging.cpp"
#include "AddCrystalToDisplayDialog.cpp"
#include "CrystalCompositionEditorDialog.cpp"
#include "RenderSetupDialog.cpp"
#include "RenderingProcessFrame.cpp"
#include "HaloRenderingThread.cpp"



