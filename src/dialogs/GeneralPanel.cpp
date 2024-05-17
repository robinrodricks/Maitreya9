/***********************************************************************
 This is the source code of Maitreya, open source platform for Vedic
 and western astrology.

 File       src/dialogs/GeneralPanel.cpp
 Release    8.0
 Author     Martin Pettau
 Copyright  2003-2017 by the author

 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
************************************************************************/

#include "GeneralPanel.h"

#include "AtlasDialog.h"
#include "Conf.h"
#include "DataSet.h"
#include "guibase.h"
#include "Lang.h"
#include "LanguageConfig.h"
#include "mvalidator.h"

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>

extern Config *config;

IMPLEMENT_CLASS( GeneralPanel, ConfigPanel )

enum { CD_SEARCHLOCATION = wxID_HIGHEST + 1, CD_NAME, CD_TIMER, CD_LONGITUDE, CD_LATITUDE, CD_LANGUAGE };

#ifdef __WXMSW__
//#if true
#define SHOW_LANGUARGES
#endif

/*************************************************//**
*
* 
*
******************************************************/
struct GeneralPanelModel : public LocationModel
{
	GeneralPanelModel() : LocationModel()
	{
		defaultStyle = 0;
		openNewDocOnStart = true;
		askOnQuit = false;
	}

	GeneralPanelModel( const Location &l ) : LocationModel( l )
	{
		defaultStyle = 0;
		openNewDocOnStart = true;
		askOnQuit = false;
	}

	int defaultStyle;
	bool openNewDocOnStart;
	bool askOnQuit;
	wxString lang;
};

/*****************************************************
**
**   GeneralPanel   ---   Constructor
**
******************************************************/
GeneralPanel::GeneralPanel( wxWindow* parent ) : ConfigPanel( parent, false )
{
	model = new GeneralPanelModel;
	config2model();

    // begin wxGlade: GeneralPanel::GeneralPanel
    label_defstyle = new wxStaticText(this, wxID_ANY, _("Default Style"));
    const wxString choice_defstyle_choices[] = {
        _("Vedic"),
        _("Western"),
    };
    choice_defstyle = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, choice_defstyle_choices);
    label_lang = new wxStaticText(this, wxID_ANY, _("Language"));
    const wxString choice_lang_choices[] = {
        _("dummy"),
        _("dummy"),
        _("dummy"),
        _("dummy"),
    };
    choice_lang = new wxChoice(this, CD_LANGUAGE, wxDefaultPosition, wxDefaultSize, 4, choice_lang_choices);
    check_opennewdoc = new wxCheckBox(this, wxID_ANY, _("Open New Document on Startup"));
    check_askonquit = new wxCheckBox(this, wxID_ANY, _("Ask on Quit"));
    text_name = new wxTextCtrl(this, CD_NAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    button_search = new wxButton(this, CD_SEARCHLOCATION, _("Search ..."));
    label_longitude = new wxStaticText(this, wxID_ANY, _("Longitude"));
    text_longitude = new wxTextCtrl(this, CD_LONGITUDE, wxEmptyString);
    const wxString choice_ew_choices[] = {
        _("East"),
        _("West"),
    };
    choice_ew = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, choice_ew_choices);
    label_latitude = new wxStaticText(this, wxID_ANY, _("Latitude"));
    text_latitude = new wxTextCtrl(this, CD_LATITUDE, wxEmptyString);
    const wxString choice_ns_choices[] = {
        _("North"),
        _("South"),
    };
    choice_ns = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, choice_ns_choices);
    label_localtime = new wxStaticText(this, wxID_ANY, _("Local Time"));
    text_localtime = new wxStaticText(this, wxID_ANY, _("00:00:00"));
    label_uttime = new wxStaticText(this, wxID_ANY, _("Universal Time"));
    text_uttime = new wxStaticText(this, wxID_ANY, _("00:00:00"));
    label_tzoffset = new wxStaticText(this, wxID_ANY, _("Time Zone Offset"));
    text_tzoffset = new wxStaticText(this, wxID_ANY, _("+00:00"));
    label_systemdst = new wxStaticText(this, wxID_ANY, _("Daylight Saving"));
    text_systemdst = new wxStaticText(this, wxID_ANY, _("+00:00"));

    set_properties();
    do_layout();
    // end wxGlade

	choice_defstyle->SetValidator( MChoiceValidator( &model->defaultStyle ));
	check_opennewdoc->SetValidator( MCheckValidator( &model->openNewDocOnStart ));
	check_askonquit->SetValidator( MCheckValidator( &model->askOnQuit ));

	text_name->SetValidator( MTextValidator( &model->locname ));
	text_longitude->SetValidator( MDegreeValidator( &model->longitude, 180 ));
	choice_ew->SetValidator( MChoiceValidator( &model->c_longitude ));
	text_latitude->SetValidator( MDegreeValidator( &model->latitude, 90 ));
	choice_ns->SetValidator( MChoiceValidator( &model->c_latitude ));

	timer = new wxTimer( this, CD_TIMER );

	Connect( CD_SEARCHLOCATION, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneralPanel::OnSearchLocation ));
	Connect( CD_TIMER, wxEVT_TIMER, wxTimerEventHandler( GeneralPanel::OnTimer ));
	Connect( CD_NAME, wxEVT_COMMAND_TEXT_ENTER, wxTextEventHandler( GeneralPanel::OnSearchLocation ));
	Connect( CD_LANGUAGE, wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GeneralPanel::OnLanguageChoice ));

	choice_lang->Clear();
#ifdef SHOW_LANGUARGES
	std::list<LanguageEntry>::iterator iter;
	int thelang = 0, i = 0;
	std::list<LanguageEntry> thelist = LanguageConfig::get()->getLanguages();
	for ( iter = thelist.begin(); iter != thelist.end(); iter++ )
	{
		choice_lang->Append( (*iter).name );
		if ( (*iter).code == config->lang ) thelang = i;
		i++;
	}
	choice_lang->SetSelection( thelang );
#else
	wxLocale *locale = LanguageConfig::get()->getLocale();
	choice_lang->Append( locale->GetName());
	choice_lang->SetSelection( 0 );
	label_lang->Enable( false );
	choice_lang->Enable( false );
#endif

	updateTzItems();
	text_name->SetFocus();
}

/*****************************************************
**
**   GeneralPanel   ---   Destructor
**
******************************************************/
GeneralPanel::~GeneralPanel()
{
	if ( timer->IsRunning()) timer->Stop();
	delete model;
}

/*****************************************************
**
**   GeneralPanel   ---   config2model
**
******************************************************/
void GeneralPanel::config2model()
{
	model = new GeneralPanelModel( *config->defaultLocation );

	model->defaultStyle = config->preferVedic ? 0 : 1;
	model->openNewDocOnStart = config->openNewDocOnStart;
	model->askOnQuit = config->askOnQuit;
	model->lang = config->lang;
}

/*****************************************************
**
**   GeneralPanel   ---   model2config
**
******************************************************/
void GeneralPanel::model2config()
{
	config->preferVedic = model->defaultStyle == 0;
	config->openNewDocOnStart = model->openNewDocOnStart;
	config->askOnQuit = model->askOnQuit;
	config->lang = model->lang;

	config->defaultLocation->setLocation(
		model->locname,
		model->getLongitude(),
		model->getLatitude(),
		model->getTimezone(),
		model->dst );
}

/*****************************************************
**
**   GeneralPanel   ---   onActivate
**
******************************************************/
void GeneralPanel::onActivate()
{
	if ( ! timer->IsRunning() ) timer->Start( 1000 );
}

/*****************************************************
**
**   GeneralPanel   ---   OnLanguageChoice
**
******************************************************/
void GeneralPanel::OnLanguageChoice( wxCommandEvent& )
{
	static bool already_shown = false;

	std::list<LanguageEntry>::iterator iter;
	wxString sellang = choice_lang->GetStringSelection();
	wxString oldlang = model->lang;
	std::list<LanguageEntry> thelist = LanguageConfig::get()->getLanguages();
	for ( iter = thelist.begin(); iter != thelist.end(); iter++ )
	{
		if ( sellang == (*iter).name )
		{
			model->lang = (*iter).code;
			break;
		}
	}
	if ( ! already_shown && model->lang != oldlang && ! config->viewprefs->doNotShowAgainAfterLanguageChange )
	{
		DoNotShowAgainDialog dialog( this,
			_("The language will be changed when you restart the program."),
			&config->viewprefs->doNotShowAgainAfterLanguageChange );
		dialog.ShowModal();
		already_shown = true;
	}
	setDirty();
}

/*****************************************************
**
**   GeneralPanel   ---   onPassivate
**
******************************************************/
void GeneralPanel::onPassivate()
{
	if ( timer->IsRunning()) timer->Stop();
}

/*****************************************************
**
**   GeneralPanel   ---   OnTimer
**
******************************************************/
void GeneralPanel::OnTimer( wxTimerEvent& )
{
	updateTzItems();
}

/*****************************************************
**
**   GeneralPanel   ---   updateTzItems
**
******************************************************/
void GeneralPanel::updateTzItems()
{
	TzUtil util;
	TzInfo tzinfo = util.getCurrentTzInfo();

	text_localtime->SetLabel( tzinfo.localTimeFormatted );
	text_uttime->SetLabel( tzinfo.utcTimeFormatted );
	text_tzoffset->SetLabel( tzinfo.tzOffsetFormatted );
	text_systemdst->SetLabel( tzinfo.dstOffsetFormatted );
}

/*****************************************************
**
**   GeneralPanel   ---   OnSearchLocation
**
******************************************************/
void GeneralPanel::OnSearchLocation( wxCommandEvent& )
{
	TransferDataFromWindow();
	AtlasDialogWrapper dialog( this, ATLASDIALOG_CALLER_DEFAULTLOCATIONPANEL, text_name->GetValue() );
	if ( dialog.run() == wxID_OK )
	{
		AtlasEntry *e = dialog.getSelectedEntry();
		model->locname = e->name;
		model->longitude = e->a_longitude;
		model->c_longitude = e->c_longitude;
		model->latitude = e->a_latitude;
		model->c_latitude = e->c_latitude;
		TransferDataToWindow();
		setDirty();
	}
}

/*****************************************************
**
**   GeneralPanel   ---   restoreDefaults
**
******************************************************/
void GeneralPanel::restoreDefaults()
{
	// not avtive on this panel
	assert( false );
}

/*****************************************************
**
**   GeneralPanel   ---   set_properties
**
******************************************************/
void GeneralPanel::set_properties()
{
    // begin wxGlade: GeneralPanel::set_properties
    choice_defstyle->SetSelection(0);
    choice_lang->SetSelection(0);
    check_askonquit->SetMinSize(wxSize(150, 24));
    choice_ew->SetSelection(0);
    choice_ns->SetSelection(0);
    // end wxGlade
}

/*****************************************************
**
**   GeneralPanel   ---   do_layout
**
******************************************************/
void GeneralPanel::do_layout()
{
    // begin wxGlade: GeneralPanel::do_layout
    wxFlexGridSizer* sizer_main = new wxFlexGridSizer(2, 1, 0, 0);
    wxStaticBoxSizer* sizer_default_location = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Standard Location")), wxVERTICAL);
    wxBoxSizer* sizer_bottom = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_tzsettings = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Timezone System Settings")), wxVERTICAL);
    wxGridSizer* grid_systemsettings = new wxGridSizer(4, 2, 3, 6);
    wxStaticBoxSizer* sizer_coordinates = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Coordinates")), wxHORIZONTAL);
    wxFlexGridSizer* grid_coordinates = new wxFlexGridSizer(2, 3, 3, 3);
    wxBoxSizer* sizer_locname = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_top = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_2 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Window Life Cycle")), wxVERTICAL);
    wxStaticBoxSizer* sizer_general = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("General")), wxVERTICAL);
    wxFlexGridSizer* grid_general = new wxFlexGridSizer(2, 2, 3, 3);
    grid_general->Add(label_defstyle, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    grid_general->Add(choice_defstyle, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    grid_general->Add(label_lang, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    grid_general->Add(choice_lang, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 3);
    grid_general->AddGrowableCol(1);
    sizer_general->Add(grid_general, 1, wxALL, 3);
    sizer_top->Add(sizer_general, 1, wxALL, 3);
    sizer_2->Add(check_opennewdoc, 0, wxALL|wxEXPAND, 1);
    sizer_2->Add(check_askonquit, 0, wxALL|wxEXPAND, 1);
    sizer_top->Add(sizer_2, 1, wxEXPAND, 0);
    sizer_main->Add(sizer_top, 1, wxEXPAND, 0);
    sizer_locname->Add(text_name, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    sizer_locname->Add(button_search, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3);
    sizer_default_location->Add(sizer_locname, 0, wxALL|wxEXPAND, 3);
    grid_coordinates->Add(label_longitude, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    grid_coordinates->Add(text_longitude, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 3);
    grid_coordinates->Add(choice_ew, 0, wxALL|wxEXPAND, 3);
    grid_coordinates->Add(label_latitude, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    grid_coordinates->Add(text_latitude, 0, wxALL|wxEXPAND, 3);
    grid_coordinates->Add(choice_ns, 0, wxALL|wxEXPAND, 3);
    grid_coordinates->AddGrowableCol(1);
    sizer_coordinates->Add(grid_coordinates, 1, wxALL, 3);
    sizer_bottom->Add(sizer_coordinates, 1, wxEXPAND, 0);
    grid_systemsettings->Add(label_localtime, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(text_localtime, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(label_uttime, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(text_uttime, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(label_tzoffset, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(text_tzoffset, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(label_systemdst, 0, wxALIGN_CENTER_VERTICAL, 0);
    grid_systemsettings->Add(text_systemdst, 0, wxALIGN_CENTER_VERTICAL, 0);
    sizer_tzsettings->Add(grid_systemsettings, 1, wxALL, 3);
    sizer_bottom->Add(sizer_tzsettings, 0, wxALL, 3);
    sizer_default_location->Add(sizer_bottom, 1, wxALL|wxEXPAND, 3);
    sizer_main->Add(sizer_default_location, 1, wxEXPAND, 0);
    SetSizer(sizer_main);
    sizer_main->Fit(this);
    // end wxGlade
}

/*****************************************************
**
**   ConfigPanelFactory   ---   createGeneralPanel
**
******************************************************/
ConfigPanel *ConfigPanelFactory:: createGeneralPanel( wxWindow *parent )
{
	return new GeneralPanel( parent );
}


