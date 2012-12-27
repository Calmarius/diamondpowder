
//(*InternalHeaders(HexagonalPrismGeneratorDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(HexagonalPrismGeneratorDialog)
const long HexagonalPrismGeneratorDialog::ID_STATICTEXT1 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_TEXTCTRL1 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_RADIOBUTTON1 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_RADIOBUTTON2 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_STATICTEXT2 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_TEXTCTRL2 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_RADIOBUTTON3 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_STATICTEXT3 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_TEXTCTRL3 = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_BUTTON_GENERATEPRISM = wxNewId();
const long HexagonalPrismGeneratorDialog::ID_CANCEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(HexagonalPrismGeneratorDialog,wxDialog)
	//(*EventTable(HexagonalPrismGeneratorDialog)
	//*)
END_EVENT_TABLE()

HexagonalPrismGeneratorDialog::HexagonalPrismGeneratorDialog(Mesh &_mesh, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size):
    mesh(_mesh)
{
	//(*Initialize(HexagonalPrismGeneratorDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Height (unit is the diameter of the hexagon face):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	prismHeightTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(prismHeightTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	regularRadioButton = new wxRadioButton(this, ID_RADIOBUTTON1, _("Regular"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	regularRadioButton->SetValue(true);
	BoxSizer3->Add(regularRadioButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	kernPrismRadioButton = new wxRadioButton(this, ID_RADIOBUTTON2, _("Kern prism"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	BoxSizer5->Add(kernPrismRadioButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Side face ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer6->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sideFaceRatioTextBox = new wxTextCtrl(this, ID_TEXTCTRL2, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	sideFaceRatioTextBox->Disable();
	BoxSizer6->Add(sideFaceRatioTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(BoxSizer6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	parryPlateRadioButton = new wxRadioButton(this, ID_RADIOBUTTON3, _("Parry plate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	BoxSizer4->Add(parryPlateRadioButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Height:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer7->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	parryPlateHeightTextBox = new wxTextCtrl(this, ID_TEXTCTRL3, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	parryPlateHeightTextBox->Disable();
	BoxSizer7->Add(parryPlateHeightTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(BoxSizer7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	generatePrismButton = new wxButton(this, ID_BUTTON_GENERATEPRISM, _("Generate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_GENERATEPRISM"));
	BoxSizer2->Add(generatePrismButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelPrismGenerationButton = new wxButton(this, ID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCEL"));
	BoxSizer2->Add(cancelPrismGenerationButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&HexagonalPrismGeneratorDialog::OnRegularRadioButtonSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&HexagonalPrismGeneratorDialog::OnKernPrismRadioButtonSelect);
	Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&HexagonalPrismGeneratorDialog::OnParryPlateRadioButtonSelect);
	Connect(ID_BUTTON_GENERATEPRISM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HexagonalPrismGeneratorDialog::OngeneratePrismClick);
	Connect(ID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HexagonalPrismGeneratorDialog::OncancelPrismGenerationClick);
	//*)
}

HexagonalPrismGeneratorDialog::~HexagonalPrismGeneratorDialog()
{
	//(*Destroy(HexagonalPrismGeneratorDialog)
	//*)
}


void HexagonalPrismGeneratorDialog::OngeneratePrismClick(wxCommandEvent& event)
{
    const double SIN60 = 0.866025404;
    double basicPoints[6][2] =
    {
        {1, 0},
        {0.5, SIN60},
        {-0.5, SIN60},
        {-1, 0},
        {-0.5, -SIN60},
        {0.5, -SIN60}
    };
    double prismHeight;
    prismHeightTextCtrl->GetValue().ToDouble(&prismHeight);
    vector<int> face;

    if (kernPrismRadioButton->GetValue())
    {
        // Create Kern basic points.
        double sideFaceRatio;
        sideFaceRatioTextBox->GetValue().ToDouble(&sideFaceRatio);
        const double ANG120 = 3.1415926526 * 2.0/3.0;
        double angle1 = ANG120 * (sideFaceRatio) / (1 + sideFaceRatio);
        for (int i = 0; i < 3; i++)
        {
            double x = 1;
            double y = 0;
            rotate2d(x, y, i * ANG120);
            basicPoints[2 * i][0] = x;
            basicPoints[2 * i][1] = y;
            x = 1;
            y = 0;
            rotate2d(x, y, i * ANG120 + angle1);
            basicPoints[2 * i + 1][0] = x;
            basicPoints[2 * i + 1][1] = y;
        }
    }
    else if (parryPlateRadioButton->GetValue())
    {
        double height;
        parryPlateHeightTextBox->GetValue().ToDouble(&height);
        for (int i = 0; i < 6; i++)
        {
            double tmpx = basicPoints[i][0];
            double tmpy = basicPoints[i][1];


            if (tmpx < 0)
            {
                basicPoints[i][0] = tmpx * height + (1 - height)*-1;
                basicPoints[i][1] = tmpy * height;
            }
            else
            {
                basicPoints[i][0] = tmpx * height + (1 - height);
                basicPoints[i][1] = tmpy * height;
            }
        }
    }

    initMesh(mesh);
    // Set vertices
    // First 6 vertex is for the front hexagonal face.
    for (int i = 0; i < 6; i++)
    {
        mesh.vertices.push_back(Vector3(basicPoints[i][0], basicPoints[i][1], prismHeight));
    }
    // Next 6 vertex is for the back hexagonal face
    for (int i = 0; i < 6; i++)
    {
        mesh.vertices.push_back(Vector3(basicPoints[i][0], basicPoints[i][1], -prismHeight));
    }
    // Make front face
    face.clear();
    for (int i = 0; i < 6; i++)
    {
        face.push_back(i);
    }
    mesh.faces.push_back(face);
    // Make back face
    face.clear();
    for (int i = 0; i < 6; i++)
    {
        face.push_back(i + 6);
    }
    mesh.faces.push_back(face);
    // Make side faces
    for (int i = 0; i < 6; i++)
    {
        int j = i + 1 == 6 ? 0 : i + 1;
        face.clear();
        // Add vertices on the front face
        face.push_back(i);
        face.push_back(j);
        // Add vertices on the back face
        face.push_back(j + 6);
        face.push_back(i + 6);

        mesh.faces.push_back(face);
    }
    // Scale the prism to fit in a sphere which has unit radius.
    double vertexDistance = ~mesh.vertices[0];  // All vertices are the same distance from the center.

    for (size_t i = 0; i < mesh.vertices.size(); i++)
    {
         mesh.vertices[i] /= vertexDistance;
    }


    EndModal(ID_BUTTON_GENERATEPRISM);
}

void HexagonalPrismGeneratorDialog::OncancelPrismGenerationClick(wxCommandEvent& event)
{
    EndModal(ID_CANCEL);
}

void HexagonalPrismGeneratorDialog::OnRegularRadioButtonSelect(wxCommandEvent& event)
{
    sideFaceRatioTextBox->Disable();
    parryPlateHeightTextBox->Disable();
}

void HexagonalPrismGeneratorDialog::OnKernPrismRadioButtonSelect(wxCommandEvent& event)
{
    sideFaceRatioTextBox->Enable();
    parryPlateHeightTextBox->Disable();
}

void HexagonalPrismGeneratorDialog::OnParryPlateRadioButtonSelect(wxCommandEvent& event)
{
    sideFaceRatioTextBox->Disable();
    parryPlateHeightTextBox->Enable();
}
