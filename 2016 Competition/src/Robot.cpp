#include <Autonomous/AutonomousDemo.hpp>
#include <Autonomous/AutonomousLowBar.hpp>
#include <Autonomous/AutonomousRockWall.hpp>
#include <Autonomous/AutonomousRoughTerrain.hpp>
#include <Autonomous/AutonomousRampParts.hpp>
#include <Autonomous/AutonomousMoat.hpp>
#include <Autonomous/AutonomousReach.hpp>
#include <Autonomous/AutonomousTimed.hpp>
#include <Autonomous/AutonomousNone.hpp>
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
            STOPPED, AUTO, TELEOP, TEST
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

        AnalogOutput* pressureSensor;

        State gameState;

        // float pressure = 0;

        void RobotInit()
        {
            // Sets up the joysticks.
            joystickPrimary = new Joystick(JOYSTICK_PRIMARY);
            joystickSecondary = new Joystick(JOYSTICK_SECONDARY);

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
            pressureSensor = new AnalogOutput(1);

            // Creates the auto modes.
            selectedAuto = NULL;
            autoChooser = new SendableChooser();
            new AutonomousLowBar(autoChooser, false, driveTrain);
            new AutonomousRockWall(autoChooser, false, driveTrain);
            new AutonomousRoughTerrain(autoChooser, false, driveTrain);
            new AutonomousRampParts(autoChooser, false, driveTrain);
            new AutonomousMoat(autoChooser, false, driveTrain);
            new AutonomousDemo(autoChooser, true, driveTrain);
            new AutonomousReach(autoChooser, true, driveTrain);
            new AutonomousTimed(autoChooser, true, driveTrain);
            new AutonomousNone(autoChooser, true);
            SmartDashboard::PutData("Auto Modes", autoChooser);

            // Sets up the game states.
            gameState = State::STOPPED;
        }

        void ComponentsUpdate(bool teleop)
        {
            vision->ComponentUpdate(teleop);
            climber->ComponentUpdate(teleop);

            driveTrain->SetCrossing(climber->IsClimbing());
            driveTrain->ComponentUpdate(teleop);

            if (!climber->IsClimbing())
            {
                collector->ComponentUpdate(teleop);
                shooter->ComponentUpdate(teleop);
            }

            // pressure = (250 * (pressureSensor->GetVoltage() / 5)) - 25;

            SmartDashboard::PutNumber("NavX Angle", ahrs->GetAngle());
            SmartDashboard::PutNumber("NavX Angle Pitch", ahrs->GetPitch());
            SmartDashboard::PutNumber("NavX Angle Yaw", ahrs->GetYaw());
            SmartDashboard::PutNumber("NavX Angle Roll", ahrs->GetRoll());
            SmartDashboard::PutNumber("NavX Velocity X", ahrs->GetVelocityX());
            SmartDashboard::PutNumber("NavX Velocity Y", ahrs->GetVelocityY());
            SmartDashboard::PutNumber("NavX Velocity Z", ahrs->GetVelocityZ());
            // SmartDashboard::PutNumber("Pressure", pressure);
        }

        void AutonomousInit()
        {
            selectedAuto = (IAutonomous*) autoChooser->GetSelected();
            ahrs->Reset();
            gameState = State::AUTO;
            climber->Init();
            selectedAuto->Start();
        }

        void AutonomousPeriodic()
        {
            SmartDashboard::PutString("Auto Selected", ((IAutonomous*) autoChooser->GetSelected())->GetName());

            if (selectedAuto != NULL)
            {
                double time = DriverStation::GetInstance().GetMatchTime();
                // bool autoRunning = selectedAuto->AutonomousUpdate(time);
                selectedAuto->AutonomousDashboard();
                selectedAuto->Run(time);
                ComponentsUpdate(false);

//                if (!autoRunning)
//                {
//                    selectedAuto = NULL;
//                }
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
            climber->Init();
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
