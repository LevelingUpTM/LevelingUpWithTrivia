using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class GameRoomViewModel : ObservableObject
    {
        [ObservableProperty] private string currentQuestion = ;
        [ObservableProperty] private string answer1 = ;
        [ObservableProperty] private string answer2 = ;
        [ObservableProperty] private string answer3 = ;
        [ObservableProperty] private string answer4 = ;

        [ObservableProperty] private int questionsLeft = 0;
        [ObservableProperty] private int correctAnswers = 0;
        [ObservableProperty] private int timeLeft = ;

        [RelayCommand]
        public void SelectAnswer(object parameter)
        {
            //
        }

        [RelayCommand]
        public void LeaveRoom()
        {
            //
        }
    }
}

