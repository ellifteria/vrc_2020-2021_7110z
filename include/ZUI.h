/*
File containing classes making up the UI
*/
#include <vector>
#include <string>
#include <map>

#include "vex.h"

using namespace std;
using namespace vex;

/*
Tiles are named by three digit codes

Digit 1: Alliance (or skills)
  1: Red
  2: Blue
  3: Skills

Digit 2: Row
  1: Home row
  2: 1 past home row
  3: 2 past home row
  etc.

Digit 3: Column
  1: Farthest left
  2: Second farthest left
  etc.

Autonomous programs have a fourth digit indicating which program it is
  (Digit is 1 unless tiles have multiple programs)
*/


//Standard thickness for graphics
int stdThk = 6;

//Color variables
color greenColor = color(0, 74, 5);
color blueColor = color(15, 0, 110);
color redColor = color(100 , 10, 0);
color yellowColor = color(230, 184, 0);
color lightGreyColor = color(125, 125, 125);
color greyColor = color(60, 60, 60);

class ZUI_Settings //Settings stored autonomous program options and selects program to run
{
  protected:
  //Variables for autonomous program selection
  map<int, string> autonNames;
  int selectedAuton;

  public:

  ZUI_Settings(){}

  void addAuton(int inAuton, string inName)
  {
    autonNames.insert(pair<int, string >(inAuton, inName) );
  }

  void setAuton(int inAuton)
  {
    selectedAuton = inAuton;
  }

  int getAuton()
  {
    return selectedAuton;
  }

  string nameFromID(int inVal)
  {
    return autonNames[inVal];
  }

  string parseAuton(int inAuton, int inKey) //Returns auton name (inKey == 0) or description (inKey == 2)
  {
    string tmp_auton = nameFromID(inAuton);
    if(inKey == 0)
    {
      tmp_auton = tmp_auton.substr(0, tmp_auton.find(";"));
    }
    else
    {
      tmp_auton.erase(0, tmp_auton.find(";")+1);
    }
    return tmp_auton;
  }
};

ZUI_Settings Settings = ZUI_Settings();

class ZUI_Text //Class for captions on UI
{
  protected:
  string txt;
  int x;
  int y;

  public:

  ZUI_Text(string inTxt, int inX, int inY)
  {
    x = inX;
    y = inY;
    txt = inTxt;
  }

  void draw()
  {
    Brain.Screen.printAt(x, y, txt.c_str());
  }

};

class ZUI_Button //BACK BUTTON JUST ANOTHER BUTTON WITH TEXT '<'
{
    protected:

    int x;
    int y;
    int sizeX;
    int sizeY;
    string cmd;
    string txt;
    color col;

    public:

    ZUI_Button(int inX, int inY, int inSizeX, int inSizeY, color inCol, string inTxt, string inCmd)
    {
        x = inX;
        y = inY;
        sizeX = inSizeX;
        sizeY = inSizeY;
        col = inCol;
        cmd = inCmd;
        txt = inTxt;
    }

    bool contains(int inX, int inY) //Checks if coordinates in parameters fall within button
    {
        if((inX >= x && inX <= x+sizeX) && (inY >= y && inY <= y +sizeY))
        {
          return true;
        }
        
        else
        {
          return false;
        }
    }

    void draw()
    {
      Brain.Screen.setPenWidth(stdThk);
      Brain.Screen.setPenColor(col);
      Brain.Screen.drawLine(x,y,x+sizeX,y);
      Brain.Screen.drawLine(x+sizeX,y,x+sizeX,y+sizeY);
      Brain.Screen.drawLine(x+sizeX,y+sizeY,x,y+sizeY);
      Brain.Screen.drawLine(x,y+sizeY,x,y);
      //DRAWTEXT
      Brain.Screen.printAt(x+stdThk, y+sizeY-stdThk*3/2, txt.c_str());
    }

    string getCmd() //Return button's command
    {
      return cmd;
    }

};

class ZUI_GameTile //Class for creating game tile images on UI
{
    protected:

    int x;
    int y;
    int sizeX;
    int sizeY;
    string type;

    public:

    ZUI_GameTile(int inX, int inY, int inSizeX, int inSizeY, string inType)
    {
        x = inX;
        y = inY;
        sizeX = inSizeX;
        sizeY = inSizeY;
        type = inType;
    }

    void setType(string inType)
    {
      type = inType;
    }

    string getType()
    {
      return type;
    }

    color getColor() //Color depends on game tile type
    {
      color clr;
      //SWITCH CASE FOR COLOR BASED ON TYPE
      string gtype = getType();
      if(gtype.compare("grey")==0)
      {
        clr = greyColor;
      }
      else if (gtype.compare("red")==0)
      {
        clr = redColor;
      }
      else if (gtype.compare("blue")==0)
      {
        clr = blueColor;
      }
      else if (gtype.compare("green")==0)
      {
        clr = greenColor;
      }
      else if (gtype.compare("selected")==0)
      {
        clr = yellowColor;
      }
      else//i.e. type == locked
      {
        clr = black;
      }
      return clr;
    }

    void draw()
    {
      Brain.Screen.setPenColor(lightGreyColor);
      Brain.Screen.setPenWidth(1);
      Brain.Screen.drawRectangle(x, y, sizeX, sizeY, getColor());
    }

};

class ZUI_Page //Class for designing pages of UI
{
    protected:

    vector<ZUI_Button> buttons;
    vector<ZUI_GameTile> tiles;
    vector<ZUI_Text> texts;

    public:

    ZUI_Page(){}

    void add(ZUI_Button inButton)
    {
        buttons.push_back(inButton);
    }
    
    vector<ZUI_Button> getButtons()
    {
        return buttons;
    }

    void add(ZUI_GameTile inTile)
    {
        tiles.push_back(inTile);
    }
    
    vector<ZUI_GameTile> getTiles()
    {
        return tiles;
    }

    void add(ZUI_Text inText)
    {
        texts.push_back(inText);
    }
    
    vector<ZUI_Text> getTexts()
    {
        return texts;
    }
    
    void erase()
    {
        buttons.clear();
        tiles.clear();
        texts.clear();
    }

    void eraseTexts()
    {
        texts.clear();
    }

    void eraseButtons()
    {
        buttons.clear();
    }

    void draw()
    {
      //DRAW IMAGES
      for(ZUI_GameTile g : tiles)
      {
        g.draw();
      }

      //DRAW TEXT
      for(ZUI_Text t : texts)
      {
        t.draw();
      }

      //DRAW BACKGROUND
      Brain.Screen.setPenWidth(stdThk);
      Brain.Screen.setPenColor(greenColor);
      Brain.Screen.drawLine(255, 15, 255, 225);
      Brain.Screen.drawLine(255, 225, 465, 225);
      Brain.Screen.drawLine(465, 225, 465, 15);
      Brain.Screen.drawLine(465, 15, 255, 15);

      //DRAW BUTTONS
      for(ZUI_Button b : buttons)
      {
        b.draw();
      }
    }
};

class ZUI_Screen //Class storing pages and controlling UI
{
    protected:

    map<int, ZUI_Page > pages;

    int currPage = 0;
    int prevPage = -1;
    bool running;
    string cmd;

    public:

    ZUI_Screen(){}

    void addPage(int ID, ZUI_Page inPage)
    {
        pages.insert(pair<int, ZUI_Page >(ID, inPage) );
    }

    void createFinalPage() //Creates last page of UI, UI ends at this page
    {
      Brain.Screen.clearScreen(greyColor);
      running = false;
      currPage = prevPage;
    }

    void updateScreen()
    {
      if(currPage != prevPage)
      {
        prevPage = currPage;
        Brain.Screen.clearScreen(color::black);
        pages[currPage].draw();
      }
    }

    void executeCmd(string cmd) //Executes command associated with button pressed
    {
      //Commands are in the form of ___=___;___=___;___=___;...___=___
      //"=" indicates changing UI or robot settings to new value
      //";" seperates command segments
      string d1 = ";";
      string d2 = "=";
      size_t pos = 0;
      
      string token;
      string func;
      string param;
      while ((pos = cmd.find(d1)) != std::string::npos) //Goes through command segments up until last segment of command
      {
        token = cmd.substr(0, pos);
        func = token.substr(0, token.find(d2));
        param = token.substr(token.find(d2)+1);

        //SWITCH CASE FOR CMD FROM BUTTON
        if(func.compare("page")==0) //Set page to new value
        {
          currPage = atoi(param.c_str());
        }
        else if(func.compare("auton")==0) //Set autonomous program
        {
          Settings.setAuton(atoi(param.c_str()));
        }
        else if(func.compare("run")==0) //Set UI running to true/false
        {
          if(param.compare("true")==0)
          {
            running = true;
          }
          else if(param.compare("false")==0)
          {
            running = false;
          }
        }
        else if(func.compare("finalpage")==0) //Change page to final page
        {
          if(param.compare("true")==0)
          {
            createFinalPage();
          }
        }
        cmd.erase(0, pos + d1.length()); //Delete command up until point to move to next command
      }
      //Read and execute last segment of command
      func = cmd.substr(0, cmd.find(d2));
      param = cmd.substr(cmd.find(d2)+1);
      if(func.compare("page")==0)
      {
        currPage = atoi(param.c_str());
      }
      else if(func.compare("auton")==0)
      {
        Settings.setAuton(atoi(param.c_str()));
      }
      else if(func.compare("run")==0)
      {
        if(param.compare("true")==0)
        {
          running = true;
        }
        else if(param.compare("false")==0)
        {
          running = false;
        }
      }
      else if(func.compare("finalpage")==0)
      {
        if(param.compare("true")==0)
        {
          createFinalPage();
        }
      }
    }

    void handleUI()
    {
      running = true;
    
      while(running == true) //Continuously check for presses on UI
      {
        /*
        When the screen is pressed, the code checks if any button was pressed
        If a button was pressed, that button's command is collected
        Then, the command is executed
        */
        cmd = "-"; //Reset command to blank command
        if(Brain.Screen.pressing())
        {
          //If screen is pressed, collect location of press
          int x = Brain.Screen.xPosition();
          int y = Brain.Screen.yPosition();
          
          for(ZUI_Button b : pages[currPage].getButtons()) //Check where press occurs
          {
            if(b.contains(x,y))
            {
              //Collect proper command from button
              cmd = b.getCmd();
              updateScreen();
              break;
            }
          }
          
          this_thread::sleep_for(300);
          Brain.Screen.setCursor(0, 0);          
        }
        //Execute command collected
        executeCmd(cmd);
        updateScreen();  
      }
    }
};