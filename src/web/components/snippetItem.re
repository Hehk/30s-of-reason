open Utils;

open Theme;

module Toggle = (
  val NiceComponents.span(
        ~debugName="SnippetToggle",
        [|
          Raw("float", "right"),
          Color(Colors.red),
          Raw("transition", Animation.Transition.normal),
          Padding(Spacing.small),
          BorderRadius(Frame.borderRadius),
          Select(":hover", [|BackgroundColor(Colors.red), Color(Colors.white), Raw("box-shadow", Frame.Shadow.red)|])
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

let make = (~query, ~id, ~title, ~description, ~content, _children) => {
  ...component,
  initialState,
  reducer,
  render: ({state: {jsOutput}, send}) =>
    <Card>
      <Toggle props={"onClick": () => send(ToggleJsOutput)}>
        (jsOutput ? ele_of_str("Hide JS") : ele_of_str("Show JS"))
      </Toggle>
      <H3> (ele_of_str(title)) </H3>
      <P> (ele_of_str(description)) </P>
      <Code text=content />
      (jsOutput ? <JsSnippet query id /> : ele_of_str(""))
    </Card>
};

module Loading = {
  module LoadingAnimation = (
    val NiceComponents.div(~debugName="LoadingTransition", [|Raw("animation", "loadingAnimation 3s infinite ease")|])
  );
  let component = ReasonReact.statelessComponent("SnippetLoading");
  let make = _children => {
    ...component,
    render: _self =>
      <Card>
        <LoadingAnimation>
          <H3> (ele_of_str("...")) </H3>
          <Code text="loading your future tech debt!" />
        </LoadingAnimation>
      </Card>
  };
};
