using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using BluetoothClientWP8.Resources;
using Windows.Networking.Sockets;
using Windows.Networking.Proximity;
using System.Diagnostics;
using Windows.Storage.Streams;
using System.Threading.Tasks;
using BluetoothConnectionManager;
using System.Windows.Media;

namespace BluetoothClientWP8
{
    public partial class MainPage : PhoneApplicationPage
    {
        private ConnectionManager connectionManager;

        private StateManager stateManager;

        // Constructor
        public MainPage()
        {
            InitializeComponent();
            connectionManager = new ConnectionManager();
            connectionManager.MessageReceived += connectionManager_MessageReceived;
            stateManager = new StateManager();

        }

        async void connectionManager_MessageReceived(string message)
        {
            Debug.WriteLine("Message received:" + message);
            string[] messageArray = message.Split(':');
/*            switch (messageArray[0])
            {
                case "LED_RED":
                    stateManager.RedLightOn = messageArray[1] == "ON" ? true : false;
                    Dispatcher.BeginInvoke(delegate()
                    {
                        RedButton.Background = stateManager.RedLightOn ? new SolidColorBrush(Colors.Red) : new SolidColorBrush(Colors.Black);
                    });
                break;
                case "LED_GREEN":
                    stateManager.GreenLightOn = messageArray[1] == "ON" ? true : false;
                    Dispatcher.BeginInvoke(delegate()
                    {
                        GreenButton.Background = stateManager.GreenLightOn ? new SolidColorBrush(Colors.Green) : new SolidColorBrush(Colors.Black);
                    });
                break;
                case "LED_YELLOW":
                    stateManager.YellowLightOn = messageArray[1] == "ON" ? true : false;
                    Dispatcher.BeginInvoke(delegate()
                    {
                        YellowButton.Background = stateManager.YellowLightOn ? new SolidColorBrush(Colors.Yellow) : new SolidColorBrush(Colors.Black);
                    });
                break;
                case "PROXIMITY":
                    stateManager.BodyDetected = messageArray[1] == "DETECTED" ? true : false;
                    if (stateManager.BodyDetected)
                    {
                        Dispatcher.BeginInvoke(delegate()
                        {
                            BodyDetectionStatus.Text = "Intruder detected!!!";
                            BodyDetectionStatus.Foreground = new SolidColorBrush(Colors.Red);
                        });
                        await connectionManager.SendCommand("TURN_ON_RED");
                    } else {
                        Dispatcher.BeginInvoke(delegate()
                        {
                            BodyDetectionStatus.Text = "No body detected";
                            BodyDetectionStatus.Foreground = new SolidColorBrush(Colors.White);
                        });
                    }
                    break;
            }
 */       }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            connectionManager.Initialize();
            stateManager.Initialize();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            connectionManager.Terminate();
        }

        private void ConnectAppToDeviceButton_Click_1(object sender, RoutedEventArgs e)
        {
            AppToDevice();
        }

        private async void AppToDevice()
        {
            ConnectAppToDeviceButton.Content = "Connecting...";
            PeerFinder.AlternateIdentities["Bluetooth:Paired"] = "";
            var pairedDevices = await PeerFinder.FindAllPeersAsync();

            if (pairedDevices.Count == 0)
            {
                Debug.WriteLine("No paired devices were found.");
            }
            else
            { 
                foreach (var pairedDevice in pairedDevices)
                {
                    if (pairedDevice.DisplayName == DeviceName.Text)
                    {
                        connectionManager.Connect(pairedDevice.HostName);
                        ConnectAppToDeviceButton.Content = "Connected";
                        DeviceName.IsReadOnly = true;
                        ConnectAppToDeviceButton.IsEnabled = false;
                        continue;
                    }
                }
            }
        }



        private async void HappyButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<faa";
            await connectionManager.SendCommand(command);
        }

        private async void MadButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fab";
            await connectionManager.SendCommand(command);
        }

        private async void SadButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fac";
            await connectionManager.SendCommand(command);
        }

        private async void FamousButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fad";
            await connectionManager.SendCommand(command);
        }

        private async void StopButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s";
            await connectionManager.SendCommand(command);
        }

        private async void PauseButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<p";
            await connectionManager.SendCommand(command);
        }

        private async void VolUpButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<+";
            await connectionManager.SendCommand(command);
        }

        private async void VolDownButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<-";
            await connectionManager.SendCommand(command);
        }

        private async void PlayTrackButton_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = TrackName.Text;
            await connectionManager.SendCommand(command2);
        }

        private async void Track01_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21400";
            await connectionManager.SendCommand(command2);
        }

        private async void Track02_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21600";
            await connectionManager.SendCommand(command2);
        }

        private async void Track03_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21500";
            await connectionManager.SendCommand(command2);
        }

        private async void Track04_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21700";
            await connectionManager.SendCommand(command2);
        }

        private async void Track05_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22000";
            await connectionManager.SendCommand(command2);
        }

        private async void Track06_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22100";
            await connectionManager.SendCommand(command2);
        }

        private async void Track07_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21800";
            await connectionManager.SendCommand(command2);
        }

        private async void Track08_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21900";
            await connectionManager.SendCommand(command2);
        }

        private async void Track09_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22200";
            await connectionManager.SendCommand(command2);
        }

        private async void Track10_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22300";
            await connectionManager.SendCommand(command2);
        }

        private async void Track11_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22400";
            await connectionManager.SendCommand(command2);
        }

        private async void Track12_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22600";
            await connectionManager.SendCommand(command2);
        }

        private async void Track13_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22700";
            await connectionManager.SendCommand(command2);
        }

        private async void Track14_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22800";
            await connectionManager.SendCommand(command2);
        }

        private async void Track15_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22500";
            await connectionManager.SendCommand(command2);
        }

        private async void Track16_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23100";
            await connectionManager.SendCommand(command2);
        }

        private async void Track17_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23200";
            await connectionManager.SendCommand(command2);
        }

        private async void Track18_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23300";
            await connectionManager.SendCommand(command2);
        }

        private async void Track19_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23400";
            await connectionManager.SendCommand(command2);
        }

        private async void Track20_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23500";
            await connectionManager.SendCommand(command2);
        }

        private async void Track21_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23600";
            await connectionManager.SendCommand(command2);
        }

        private async void Track22_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23700";
            await connectionManager.SendCommand(command2);
        }

        private async void Track23_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23800";
            await connectionManager.SendCommand(command2);
        }

        private async void Track24_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23900";
            await connectionManager.SendCommand(command2);
        }

        private async void Track25_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24000";
            await connectionManager.SendCommand(command2);
        }

        private async void Track26_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24100";
            await connectionManager.SendCommand(command2);
        }

        private async void Track27_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24200";
            await connectionManager.SendCommand(command2);
        }

        private async void Track28_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24400";
            await connectionManager.SendCommand(command2);
        }

        private async void Track29_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24500";
            await connectionManager.SendCommand(command2);
        }

        private async void Track30_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24600";
            await connectionManager.SendCommand(command2);
        }

        private async void Track31_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24700";
            await connectionManager.SendCommand(command2);
        }

        private async void Track32_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24800";
            await connectionManager.SendCommand(command2);
        }

        private async void Track33_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24900";
            await connectionManager.SendCommand(command2);
        }

        private async void Track34_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "25000";
            await connectionManager.SendCommand(command2);
        }

        private async void Track35_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "25100";
            await connectionManager.SendCommand(command2);
        }

        private async void Track36_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "25200";
            await connectionManager.SendCommand(command2);
        }

        private async void Track37_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "25300";
            await connectionManager.SendCommand(command2);
        }

        private async void Track38_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "25400";
            await connectionManager.SendCommand(command2);
        }

        private async void Track39_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "25500";
            await connectionManager.SendCommand(command2);
        }

        private async void Track40_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20000";
            await connectionManager.SendCommand(command2);
        }

        private async void Track41_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19900";
            await connectionManager.SendCommand(command2);
        }

        private async void Track42_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19800";
            await connectionManager.SendCommand(command2);
        }

        private async void Track43_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19700";
            await connectionManager.SendCommand(command2);
        }

        private async void Track44_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19600";
            await connectionManager.SendCommand(command2);
        }

        private async void Track45_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19500";
            await connectionManager.SendCommand(command2);
        }

        private async void Track46_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19400";
            await connectionManager.SendCommand(command2);
        }

        private async void Track47_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19300";
            await connectionManager.SendCommand(command2);
        }

        private async void Track48_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19200";
            await connectionManager.SendCommand(command2);
        }

        private async void Track49_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19100";
            await connectionManager.SendCommand(command2);
        }

        private async void Track50_Click1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "19000";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound01_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20101";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound02_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20202";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound03_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20303";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound04_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20404";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound05_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20505";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound06_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20606";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound07_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20707";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound08_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20808";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound09_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "20909";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound10_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21010";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound11_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21111";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound12_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21212";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound13_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21313";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound14_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "21614";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound15_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "22915";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound16_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "23016";
            await connectionManager.SendCommand(command2);
        }

        private async void Sound17_Click_1(object sender, RoutedEventArgs e)
        {
            string command = "<s<fb";
            await connectionManager.SendCommand(command);
            string command2 = "24300";
            await connectionManager.SendCommand(command2);
        }

    }
}