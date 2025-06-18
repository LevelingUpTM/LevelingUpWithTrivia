using System.Windows.Controls;
using LevelingUpWithTrivia.ViewModels;

namespace LevelingUpWithTrivia.Views;

public partial class WaitingForOthersView : UserControl
{
    public WaitingForOthersView()
    {
        InitializeComponent();
        DataContext = new WaitingForOthersViewModel();
    }
}
