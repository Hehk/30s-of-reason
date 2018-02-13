open Theme;

module Wrapper = (
  val NiceComponents.input(
        ~debugName="SearchWrapper",
        [|
          Raw("outline", "none"),
          Raw("border", "none"),
          Raw("box-sizing", "border-box"),
          BorderRadius(Frame.borderRadius),
          Display(Block),
          Width(Percent(100.)),
          Raw("box-shadow", Frame.Shadow.normal),
          Padding(Spacing.normal),
          MarginTop(Spacing.normal),
          Raw("font-size", Font.Size.normal),
          Raw("transition", Animation.Transition.normal),
          Select(":focus", [|Raw("box-shadow", Frame.Shadow.red)|])
        |]
      )
);

type state = {value: string};

type action =
  | ChangeValue(string);

let component = ReasonReact.reducerComponent("Search");

let reducer = (action, _state) =>
  switch action {
  | ChangeValue(newValue) => ReasonReact.Update({value: newValue})
  };

let make = (~initialValue="", ~onChange=_newValue => (), _children) => {
  ...component,
  initialState: () => {value: initialValue},
  reducer,
  render: ({send, state}) =>
    <Wrapper
      props={
        "value": state.value,
        "onChange": e => {
          let value = e##target##value;
          send(ChangeValue(value));
          onChange(value);
        }
      }
    />
};
