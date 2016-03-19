#pragma once

#include <Schematic.hpp>

using namespace std;

class IAutonomous
{
    private:
        string name;
        bool started;

    public:
        IAutonomous(SendableChooser *chooser, bool defaultChooser, string autoName)
        {
            name = autoName;
            started = false;

            if (defaultChooser)
            {
                chooser->AddDefault(name, this);
            }
            else
            {
                chooser->AddObject(name, this);
            }
        }

        virtual ~IAutonomous()
        {
        }

        bool AutonomousUpdate(const double& time)
        {
            //if (!started)
            //{
//               Start();
//                started = true;
//            }
//            else
//            {
//                bool running = Run(time);
//
//                if ((time > 15 || started) ? !Run(1000) : false || !running)
//                {
//                    Stop();
//                    return (started = false);
//                }
//            }

            return true;
        }

        void AutonomousDashboard()
        {
            SmartDashboard::PutString("Autonomous Using", name);
            SmartDashboard::PutBoolean("Autonomous Enabled", started);
        }

        virtual void Start()
        {
        }

        virtual bool Run(const double& time)
        {
            return false;
        }

        virtual void Stop()
        {
        }

        inline string GetName() const { return name; }
};
