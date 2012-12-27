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



