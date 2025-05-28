using System.Windows.Controls;
using LevelingUpWithTrivia.ViewModels;

namespace LevelingUpWithTrivia.Views;

public partial class JoinRoomView : UserControl
{
    public JoinRoomView()
    {
        InitializeComponent();
        DataContext = new JoinRoomViewModel();
    }
}