using CommunityToolkit.Mvvm.ComponentModel;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class MainWindowViewModel : ObservableObject
    {
        public static MainWindowViewModel? Current => Application.Current.MainWindow.DataContext as MainWindowViewModel;

        [ObservableProperty]
        private UIElement _content = new StartMenuView();

        public MainWindowViewModel()
        {
            //Communicator.Instance.Connect();
            //Communicator.Instance.Send(new SignupRequest("first", "pass", "adadsdsa"));
            //SignupResponse packet = (Communicator.Instance.Receive() as SignupResponse)!;
            //Console.WriteLine(packet);
        }
    }
}
