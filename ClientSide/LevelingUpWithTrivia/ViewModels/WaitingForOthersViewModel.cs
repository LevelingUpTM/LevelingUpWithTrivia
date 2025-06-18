using CommunityToolkit.Mvvm.ComponentModel;
using LevelingUpWithTrivia.Views;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using System.Windows.Threading;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class WaitingForOthersViewModel : ObservableObject
    {
        private DispatcherTimer checkTimer;

        public WaitingForOthersViewModel()
        {
            checkTimer = new DispatcherTimer();
            checkTimer.Interval = TimeSpan.FromSeconds(2);
            checkTimer.Tick += CheckIfGameFinished;
            checkTimer.Start();
        }

        private void CheckIfGameFinished(object? sender, EventArgs e)
        {
            try
            {
                Communicator.Instance.Send(new GetGameResultsRequest());
                var response = Communicator.Instance.Receive();

                if (response is GetGameResultsResponse r && r.Status == 0)
                {
                    checkTimer.Stop();
                    var vm = new GameResultsViewModel();
                    vm.LoadGameResults();
                    MainWindowViewModel.Current!.Content = new GameResultsView { DataContext = vm };
                }
            }
            catch
            {
            }
        }
    }
}