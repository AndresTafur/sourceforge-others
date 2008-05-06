

/**  Clase que muestra la pantalla de bienvenida (siendo esta un wxHtmlWindow), hereda de wxPanel
 */

class Welcome : public wxPanel
{
public:


/**  Constructor principal, llama al superconstructor wxPanel
 *   @param parent Padre del objeto.
 */


  Welcome(wxWindow *parent, wxString &path) : wxPanel(parent,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_3D,wxT("HtmlWindow"))
  {
 wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxHtmlWindow *html =  new wxHtmlWindow(this,wxID_ANY, wxDefaultPosition,wxDefaultSize,wxHW_DEFAULT_STYLE,wxT("htmlWindow"));
    html->LoadPage(wxT("http://adbux.org/"));


     sizer->Add(html, 1, wxEXPAND, 0);
     SetAutoLayout(true);

      this->SetSizer(sizer);

      sizer->Fit(this);
      sizer->SetSizeHints(this);

        Layout();

  }



};
