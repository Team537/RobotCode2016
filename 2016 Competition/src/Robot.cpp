#include <Autonomous/AutonomousBall1.hpp>
#include <Autonomous/AutonomousDemo.hpp>
#include <Autonomous/AutonomousReach.hpp>
#include <Climber/Climber.hpp>
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Vision/Vision.hpp>
#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>

using namespace std;

class Robot: public IterativeRobot
{
        enum State
        {
            STOPED, AUTO, TELEOP, TEST
        };

    private:
        SendableChooser* autoChooser;
        IAutonomous* selectedAuto;

        Joystick* joystickPrimary;
        Joystick* joystickSecondary;
        Compressor *compressor;
        AHRS *ahrs;

        Vision* vision;
        DriveTrain* driveTrain;
        Shooter* shooter;
        Climber* climber;
        Collector* collector;

        State gameState;

        void RobotInit()
        {
            // Sets up the joysticks.
            joystickPrimary = new Joystick(CONTROLLER_PRIMARY);
            joystickSecondary = new Joystick(CONTROLLER_SECONDARY);

            // Sets up robot components.
            compressor = new Compressor();

            try
            {
                ahrs = new AHRS(SPI::Port::kMXP);
                ahrs->Reset();
            }
            catch (exception ex)
            {
                std::string err_string = "Error instantiating navX-MXP:  ";
                err_string += ex.what();
                DriverStation::ReportError(err_string.c_str());
            }

            // Creates the robot components.
            vision = new Vision();
            driveTrain = new DriveTrain(joystickPrimary, joystickSecondary, ahrs, vision);
            shooter = new Shooter(joystickPrimary, joystickSecondary, vision, driveTrain);
            climber = new Climber(joystickPrimary, joystickSecondary);
            collector = new Collector(joystickPrimary, joystickSecondary);

            // Creates the auto modes.
            selectedAuto = NULL;
            autoChooser = new SendableChooser();
            new AutonomousBall1(autoChooser, false, driveTrain, shooter);
            new AutonomousDemo(autoChooser, true, driveTrain);
            new AutonomousReach(autoChooser, false, driveTrain);
            SmartDashboard::PutData("Auto Modes", autoChooser);

            // Sets up the game states.
            gameState = State::STOPED;
        }

        void ComponentsUpdate(bool teleop)
        {
            vision->ComponentUpdate(teleop);
            climber->ComponentUpdate(teleop);

            driveTrain->SetCrossing(climber->IsClimbing());
            driveTrain->ComponentUpdate(teleop);

            if (!climber->IsClimbing())
            {
                shooter->ComponentUpdate(teleop);
                collector->ComponentUpdate(teleop);
            }

            SmartDashboard::PutNumber("NavX Angle", ahrs->GetAngle());
            SmartDashboard::PutNumber("NavX Angle Pitch", ahrs->GetPitch());
            SmartDashboard::PutNumber("NavX Angle Yaw", ahrs->GetYaw());
            SmartDashboard::PutNumber("NavX Angle Roll", ahrs->GetRoll());
            SmartDashboard::PutNumber("NavX Velocity X", ahrs->GetVelocityX());
            SmartDashboard::PutNumber("NavX Velocity Y", ahrs->GetVelocityY());
            SmartDashboard::PutNumber("NavX Velocity Z", ahrs->GetVelocityZ());
        }

        void AutonomousInit()
        {
            selectedAuto = (IAutonomous*) autoChooser->GetSelected();
            ahrs->Reset();
            gameState = State::AUTO;
        }

        void AutonomousPeriodic()
        {
            SmartDashboard::PutString("Auto Selected", ((IAutonomous*) autoChooser->GetSelected())->GetName());

            if (selectedAuto != NULL)
            {
                double time = DriverStation::GetInstance().GetMatchTime();
                bool autoRunning = selectedAuto->AutonomousUpdate(time);
                selectedAuto->AutonomousDashboard();
                ComponentsUpdate(false);

                if (!autoRunning)
                {
                    selectedAuto = NULL;
                }
            }
        }

        void TeleopInit()
        {
            if (selectedAuto != NULL)
            {
                selectedAuto->AutonomousUpdate(1000);
                selectedAuto = NULL;
            }

            ahrs->Reset();
            gameState = State::TELEOP;
        }

        void TeleopPeriodic()
        {
            ComponentsUpdate(true);
        }

        void TestPeriodic()
        {
            ComponentsUpdate(true);
            LiveWindow::GetInstance()->Run();
            gameState = State::TEST;
        }
};

START_ROBOT_CLASS(Robot)
