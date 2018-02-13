open Utils;

open Theme;

module Toggle = (
  val NiceComponents.span(
        ~debugName="SnippetToggle",
        [|
          Raw("float", "right"),
          Color(Colors.red),
          Raw("transition", "0.25s ease"),
          Padding(Spacing.small),
          BorderRadius(Frame.borderRadius),
          Select(
            ":hover",
            [|
              BackgroundColor(Colors.red),
              Color(Colors.white),
              Raw("box-shadow", "0 10px 40px 0 rgba(62,57,107,0.07), 0 2px 9px 0 rgba(62,57,107,0.06)")
            |]
          )
        |]
      )
);

type state = {jsOutput: bool};

let initialState = () => {jsOutput: false};

type action =
  | ToggleJsOutput;

let reducer = (action, state) =>
  switch action {
  | ToggleJsOutput => ReasonReact.Update({jsOutput: ! state.jsOutput})
  };

let component = ReasonReact.reducerComponent("Snippet");

let make = (~id, ~title, ~description, ~content, _children) => {
  ...component,
  initialState,
  reducer,
  render: ({state: {jsOutput}, send}) =>
    <Card>
      <Toggle props={"onClick": () => send(ToggleJsOutput)}>
        (jsOutput ? str_to_ele("Hide JS") : str_to_ele("Show JS"))
      </Toggle>
      <H3> (str_to_ele(title)) </H3>
      <P> (str_to_ele(description)) </P>
      <Code text=content />
      (jsOutput ? <JsSnippet id /> : str_to_ele(""))
    </Card>
};
