#include "calculator.h"
#include "./ui_calculator.h"

double calc_val = 0.0;
bool div_trig = false;
bool mult_trig = false;
bool add_trig = false;
bool sub_trig = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // access Display using ui->Display, then type convert calc_val to set text as string
    ui->Display->setText(QString::number(calc_val));

    //creates an array of pointers to QPushButton objects
    QPushButton *num_buttons[10];

    //initializing the arary
    for (int i = 0; i < 10; ++i){
        //setting the name of button_name to the name we defined in the ui
        QString button_name = "Button" + QString::number(i);

        // looks for child widget named button_name, if found, it returns a pointer to the QPushButton object and assigns it to num_button[i]
        num_buttons[i] = Calculator::findChild<QPushButton *>(button_name);
        // sets up a connection with the release() and num_pressed() function
        //When the button is released, it executes the num_pressed() func
        connect(num_buttons[i], SIGNAL(released()), this, SLOT(num_pressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(math_button_pressed()));
    connect(ui->Sub, SIGNAL(released()), this, SLOT(math_button_pressed()));
    connect(ui->Div, SIGNAL(released()), this, SLOT(math_button_pressed()));
    connect(ui->Mult, SIGNAL(released()), this, SLOT(math_button_pressed()));

    connect(ui->Equal, SIGNAL(released()), this, SLOT(equal_button()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(clear()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::num_pressed(){
    //creates a pointer the object that sent the signal, so in this case it's QPushButton
    QPushButton *button = (QPushButton *)sender();
    //retrieves and stores text that's displayed on QPushButton, so the number that was clicked
    QString button_val = button->text();
    //retrieves and stores current text displayed on Display
    QString display_val = ui->Display->text();

    //checks if display is 0
    if ((display_val.toDouble() == 0) || (display_val.toDouble() == 0.0)){
        //sets display to value of button that was just pressed
        ui ->Display->setText(button_val);
    } else {
        //if value is not zero, concat the button that was pressed with the current display value
        QString new_val = display_val + button_val;
        //convert new val to double
        double dbl_new_val = new_val.toDouble();
        //convert new value back to string and display new value on screen with a max of 16 digits
        ui->Display->setText(QString::number(dbl_new_val, 'g', 16));
    }
}

void Calculator::math_button_pressed(){
    div_trig = false;
    mult_trig = false;
    add_trig = false;
    sub_trig = false;

    //get value of display
    QString display_val = ui->Display->text();
    //change to double
    calc_val = display_val.toDouble();
    //check who sent it
    QPushButton *button = (QPushButton *)sender();
    QString button_val = button->text();

    //compare is a instance member method, you need to use it on a object
    //methods that don't require objects are static member methods
    if (button_val.compare('/', Qt::CaseInsensitive) == 0){
        div_trig = true;
    } else if(button_val.compare('*', Qt::CaseInsensitive) == 0){
        mult_trig = true;
    } else if(button_val.compare("+", Qt::CaseInsensitive) == 0){
        add_trig = true;
    }else if(button_val.compare('-', Qt::CaseInsensitive) == 0){
        sub_trig = true;
    }

    ui->Display->setText("");

}

void Calculator::equal_button(){
    double solution = 0.0;
    //get text from display
    QString display_val = ui->Display->text();
    //toDouble is a instance member method, so you need to use it on an object
    double dbl_display_val = display_val.toDouble();

    if (add_trig || sub_trig || mult_trig || div_trig){
        if (add_trig){
            solution = calc_val + dbl_display_val;
        } else if (sub_trig){
            solution = calc_val - dbl_display_val;
        } else if (mult_trig){
            solution = calc_val * dbl_display_val;
        }else if (div_trig){
            solution = calc_val / dbl_display_val;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::clear(){
    calc_val = 0.0;
    div_trig = false;
    mult_trig = false;
    add_trig = false;
    sub_trig = false;

    ui->Display->setText(QString::number(calc_val));
}
