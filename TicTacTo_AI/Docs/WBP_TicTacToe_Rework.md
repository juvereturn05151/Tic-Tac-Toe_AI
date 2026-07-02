# WBP_TicTacToe Rework

This widget should be rebuilt in the Unreal UMG Designer, not generated at runtime.

## Main Panels

Use one root `Canvas Panel`, then create two top-level panels:

- `SelectionMenuPanel`
- `BoardPanel`

`SelectionMenuPanel` is the fighting-game-style setup screen. `BoardPanel` contains the existing board, status, and restart UI.

## SelectionMenuPanel Layout

Suggested hierarchy:

```text
SelectionMenuPanel
  HeaderText
  SideSelectionHorizontalBox
    LeftSidePanel
      Player1TitleText
      LeftControllerPreviousButton
      LeftControllerText
      LeftControllerNextButton
      LeftRLAgentPanel
        LeftRLAgentPreviousButton
        LeftRLAgentText
        LeftRLAgentNextButton
    RightSidePanel
      Player2TitleText
      RightControllerPreviousButton
      RightControllerText
      RightControllerNextButton
      RightRLAgentPanel
        RightRLAgentPreviousButton
        RightRLAgentText
        RightRLAgentNextButton
  BottomActionPanel
    MenuActionPreviousButton
    MenuActionText
    MenuActionNextButton
    MainActionButton
      MainActionButtonText
    MenuWarningText
```

The controller arrows cycle through:

- Human Player
- AI Random
- AI AlphaBeta
- AI RL

The RL agent panels are hidden unless that side is set to `AI RL`.

## Required Widget Names

These names are bound by `UTicTacToeBoardWidget`:

- `SelectionMenuPanel`
- `LeftControllerText`
- `RightControllerText`
- `LeftControllerPreviousButton`
- `LeftControllerNextButton`
- `RightControllerPreviousButton`
- `RightControllerNextButton`
- `LeftRLAgentPanel`
- `RightRLAgentPanel`
- `LeftRLAgentText`
- `RightRLAgentText`
- `LeftRLAgentPreviousButton`
- `LeftRLAgentNextButton`
- `RightRLAgentPreviousButton`
- `RightRLAgentNextButton`
- `MenuActionText`
- `MenuActionPreviousButton`
- `MenuActionNextButton`
- `MainActionButton`
- `MainActionButtonText`
- `MenuWarningText`
- `BoardPanel`

Keep the existing board widget names:

- `StatusText`
- `ModeText`
- `TileButton_0` through `TileButton_8`
- `TileText_0` through `TileText_8`
- `RestartButton`

## Future Hook Notes

- AlphaBeta AI is already connected in C++ through `ETicTacToeControllerType::AlphaBetaAI`.
- RL agent slots are represented by `ETicTacToeRLAgentSlot`.
- `AI RL` currently uses Random AI behavior as a placeholder.
- Connect saved RL agent loading in `ATicTacToeGameMode::StartConfiguredMatch`.
- Connect real RL training in `ATicTacToeGameMode::StartRLTrainingPlaceholder`.
