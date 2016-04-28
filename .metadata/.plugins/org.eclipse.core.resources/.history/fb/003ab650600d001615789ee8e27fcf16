#include <Autonomous/Autonomous.hpp>
#include <Climber/Climber.hpp>
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
//#include <Shooter/Shooter.hpp>
#include <Vision/Vision.hpp>
#include <Schematic.hpp>

using namespace std;

class Robot: public IterativeRobot
{
    private:
        SendableChooser* autoChooser;
        IAutonomous* selectedAuto;

        Vision* vision;
        DriveTrain* driveTrain;
        //Shooter* shooter;
        Climber* climber;
        Collector* collector;
        //Talon *TestTalon;
      //  CameraServer* camera;

        void RobotInit()
        {
           // camera = CameraServer::GetInstance();
            //camera->SetQuality(50);
            //camera->StartAutomaticCapture("cam0");
            AHRS* ahrs = nullptr;

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

            Schematic::Init(new Joystick(JOYSTICK_PRIMARY), new Joystick(JOYSTICK_SECONDARY), new Joystick(JOYSTICK_TERTIARY), ahrs);

            // Creates the robot components.
            vision = new Vision();
            driveTrain = new DriveTrain(vision);
           // shooter = new Shooter(vision, driveTrain);
            climber = new Climber();
            collector = new Collector();

            // Creates the auto modes.
            selectedAuto = NULL;
            autoChooser = new SendableChooser();
            new AutonomousLowBar(autoChooser, false, driveTrain, collector);
            new AutonomousLowGoal(autoChooser, false, driveTrain, collector);
            new AutonomousRockWall(autoChooser, false, driveTrain, collector);
            new AutonomousRoughTerrain(autoChooser, false, driveTrain, collector);
            new AutonomousRampParts(autoChooser, false, driveTrain, collector);
            new AutonomousMoat(autoChooser, false, driveTrain, collector);
            new AutonomousReach(autoChooser, false, driveTrain, collector);
            new AutonomousTimed(autoChooser, false, driveTrain, collector);
            new AutonomousTimedLowBar(autoChooser, true, driveTrain, collector);
            new AutonomousNone(autoChooser, false);
            SmartDashboard::PutData("Auto Modes", autoChooser);
        }

        void ComponentsUpdate(bool teleop)
        {
         //   vision->ComponentUpdate(teleop);
            climber->ComponentUpdate(teleop);

            driveTrain->SetClimbing(climber->IsClimbing());
            driveTrain->SetClimbingFullSpeed(climber->IsFullSpeed());
            driveTrain->ComponentUpdate(teleop);

            collector->ComponentUpdate(teleop);

            if (!climber->IsClimbing())
            {
           //     shooter->ComponentUpdate(teleop);
            }

            SmartDashboard::PutNumber("NavX Angle", Schematic::GetGyro()->GetAngle());
            SmartDashboard::PutNumber("NavX Angle Pitch", Schematic::GetGyro()->GetPitch());
            SmartDashboard::PutNumber("NavX Angle Yaw", Schematic::GetGyro()->GetYaw());
            SmartDashboard::PutNumber("NavX Angle Roll", Schematic::GetGyro()->GetRoll());
            SmartDashboard::PutNumber("NavX Velocity X", Schematic::GetGyro()->GetVelocityX());
            SmartDashboard::PutNumber("NavX Velocity Y", Schematic::GetGyro()->GetVelocityY());
            SmartDashboard::PutNumber("NavX Velocity Z", Schematic::GetGyro()->GetVelocityZ());
        }

        void AutonomousInit()
        {
            Schematic::GetGyro()->Reset();
            selectedAuto = (IAutonomous*) autoChooser->GetSelected();
            selectedAuto->Start();
        }

        void AutonomousPeriodic()
        {
            SmartDashboard::PutString("Auto Selected", ((IAutonomous*) autoChooser->GetSelected())->GetName());

            if (selectedAuto != NULL)
            {
                if (collector->IsCollectorDeployed())
                {
                    climber->Init();
                }
                double time = DriverStation::GetInstance().GetMatchTime();
                selectedAuto->Run(time);
                SmartDashboard::PutString("Autonomous Using", selectedAuto->GetName());
                ComponentsUpdate(false);
            }
        }

        void TeleopInit()
        {
            Schematic::GetGyro()->Reset();

//            if (selectedAuto != NULL)
//            {
//                selectedAuto = NULL;
//            }
            driveTrain->SetState(DriveTrain::DriveState::TELEOP_CONTROL);
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
        }
};

START_ROBOT_CLASS(Robot)
