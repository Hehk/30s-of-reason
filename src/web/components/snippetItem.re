open Utils;

module Toggle = (
  val NiceComponents.span(
        ~debugName="SnippetToggle",
        [|Raw("float", "right"), Color(Hex("db4d3f"))|]
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
