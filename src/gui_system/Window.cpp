#include <iostream>

#include "Window.hpp"

#include "Button.hpp"
#include "Label.hpp"
#include "ProgressBar.hpp"
#include "TextBox.hpp"

#include "../misc/MediaManager.hpp"
#include "../misc/Misc.hpp"

#include "../xml/tinyxml.h"

using namespace std;
using namespace gui;

Window::Window(){
	active_ = NULL;
	hover_ = NULL;
}

Window::Window(const Window& other){

}

Window::~Window(){
    UnLoad();
}

Control *Window::GetFromID(Control::ControlID id){
    std::vector<Control*>::const_iterator it;
    for(it=controls_.begin();it!=controls_.end();it++){
        if((*it)->GetID() == id){
            return (*it);
        }
    }
    return NULL;
}


int Window::ManageEvent(const sf::Event& event)
{
	// test effet de hover
	std::vector<Control*>::const_iterator it;

    if (event.Type == sf::Event::MouseMoved)
    {
    	Control* new_hover = GetUnderMouse(event.MouseMove.X, event.MouseMove.Y);
    	if (new_hover != NULL && new_hover != hover_)
    	{
    		// cas particulier o� la souris passe instantan�ment au dessus d'un autre contr�le
    		// (deux contr�les coll�s par exemple)
    		if (hover_ != NULL)
    		{
    			hover_->SetState(active_ == hover_ ? Control::ON_FOCUS : Control::NORMAL);
    		}
    		hover_ = new_hover;
    		hover_->SetState(Control::ON_HOVER);
    	}
    	else if (new_hover == NULL && hover_ != NULL)
    	{
    		// la souris a quitt� hover_
    		hover_->SetState(active_ == hover_ ? Control::ON_FOCUS : Control::NORMAL);
    		hover_ = NULL;
    	}
		return 0;
	}

	// on v�rifie si un contr�le doit prendre le focus
	// TODO: prendre le focus aussi avec <tab>
	if (event.Type == sf::Event::MouseButtonPressed)
	{
		Control* new_active = GetUnderMouse(event.MouseButton.X, event.MouseButton.Y);
        if (new_active != NULL && new_active != active_)
        {
        	printf(" nouveau controle actif : %u\n", new_active->GetID());
        	if  (active_ != NULL)
        	{
				active_->SetState(Control::NORMAL);
        	}
			active_ = new_active;
			active_->SetState(Control::ON_FOCUS);
        }
        else if (new_active == NULL && active_ != NULL)
        {
        	// active_ a perdu focus
        	printf(" le controle %d a perdu le focus\n", active_->GetID());
        	active_->SetState(Control::NORMAL);
        	active_ = NULL;
        }
	}

	// pas de contr�le actif = rien � faire
	if (active_ == NULL)
	{
		return 0;
	}

	if (event.Type == sf::Event::MouseButtonReleased)
	{
        if (event.MouseButton.Button == sf::Mouse::Left)
		{
			// le contr�le cliqu� est forc�ment sous la souris
			if (hover_ != NULL)
			{
				return WindowCallback(hover_->GetID(), 0, NULL);
			}
		}
	}
	else if (event.Type == sf::Event::KeyPressed)
	{
		active_->OnKeyPressed(event.Key.Code);
	}
	else if (event.Type == sf::Event::TextEntered)
	{
		active_->OnTextEntered(event.Text.Unicode);
	}

	return 0;
}


bool Window::HasFocus() const
{
	return active_ != NULL;
}


void Window::Load(const std::string& xmlfile){
    int id, x=0, y=0, w, h, alpha;
    const char* p = NULL;
    std::string temp1, temp2;

    TiXmlDocument doc;
    TiXmlElement* controls_elem, *elem;
    TiXmlNode *node;

    if (!doc.LoadFile(xmlfile.c_str())){
		std::cerr << "can't open window definitions: " << xmlfile << std::endl;
		abort();
	}

    node = doc.FirstChild("window");
    elem = node->ToElement();
    if(elem != NULL){
        if (elem->QueryIntAttribute("x", &x) != TIXML_SUCCESS){
		    cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
		}
        if (elem->QueryIntAttribute("y", &y) != TIXML_SUCCESS){
		    cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
		}
        if (elem->QueryIntAttribute("w", &w) != TIXML_SUCCESS){
		    cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
		}
        if (elem->QueryIntAttribute("h", &h) != TIXML_SUCCESS){
		    cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
		}
		if (elem->QueryIntAttribute("alpha", &alpha) != TIXML_SUCCESS){
		    alpha = -1;
		}
        p = elem->Attribute("background");
        if(p != NULL){
            SetPosition(x, y);
            background_ = GET_IMG(p);
            background_.Resize(w, h);

            if(alpha != -1)
                background_.SetColor(sf::Color(255,255,255,alpha));

            rect_.Top = y;
            rect_.Bottom = h + y;
            rect_.Left = x;
            rect_.Right = h + x;
        }
    }

	node = doc.FirstChild("window")->FirstChildElement();
	controls_elem = node->ToElement();
	while (controls_elem != NULL){

        // id du widget
        if(controls_elem->QueryIntAttribute("id", &id) != TIXML_SUCCESS){
            cout << "Warning: Aucun identifiant pour ce widget" << endl;
            id = 0;
        }

	    // Position du widget (n�c�ssaire � tout les contr�les)
		if (controls_elem->QueryIntAttribute("x", &x) != TIXML_SUCCESS){
		    cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
			x = 0;
			break;
		}
		if (controls_elem->QueryIntAttribute("y", &y) != TIXML_SUCCESS){
		    cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
			y = 0;
			break;
		}

        // Taille souhait� du widget
        if (controls_elem->QueryIntAttribute("w", &w) != TIXML_SUCCESS)
			w = Control::UNDEFINED;
		if (controls_elem->QueryIntAttribute("h", &h) != TIXML_SUCCESS)
			h = Control::UNDEFINED;

        Control::ControlPos ctrl_pos(x, y);
	    Control::ControlPos ctrl_size(w, h);

	    std::string s1 = controls_elem->Value();

	    if(s1 == "button"){
            p = controls_elem->Attribute("pic");
            if(p == NULL){
                temp1 = "";
            }else{
                temp1 = p;
            }

            p = controls_elem->Attribute("OnHover");
            if(p == NULL){
                temp2 = "";
            }else{
                temp2 = p;
            }

            controls_.push_back(new Button(id, ctrl_pos, ctrl_size, temp1, temp2));
	    }else if(s1 == "label"){
	        controls_.push_back(new Label(id, ctrl_pos, controls_elem->GetText()));
	    }
	    else if (s1 == "textbox")
	    {
			// TODO: Ajout possible d'un texte par d�faut ?
	    	controls_.push_back(new TextBox(id, ctrl_pos, w));
	    }

		controls_elem = controls_elem->NextSiblingElement();
	}
}

void Window::UnLoad(){
    std::vector<Control*>::iterator it;
    for(it=controls_.begin();it!=controls_.end();it++){
        delete (*it);
    }
    controls_.clear();
}

void Window::Render(sf::RenderTarget& app) const{
    std::vector<Control*>::const_iterator it;

    app.Draw(background_);
    for(it=controls_.begin();it!=controls_.end();it++){
        app.Draw(*(*it));
    }
}


Control* Window::GetUnderMouse(int x, int y)
{
	// transformation des coords absolues en coords relatives
	x -= GetPosition().x;
	y -= GetPosition().y;
	for (std::vector<Control*>::const_iterator it = controls_.begin();
		it != controls_.end(); ++it)
	{
		if ((**it).GetRect().Contains(x, y))
		{
			return *it;
		}
	}
	return NULL;
}