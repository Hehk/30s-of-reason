open Utils;

open Theme;

module Wrapper = (
  val NiceComponents.code(
        ~debugName="Code",
        [|
          Display(Block),
          Padding(Spacing.normal),
          BorderRadius(Frame.borderRadius),
          MarginBottom(Spacing.normal),
          BackgroundColor(Colors.black),
          Color(Colors.gray),
          Raw("box-shadow", Frame.Shadow.normal),
          Raw("font-size", "1rem"),
          LineHeight(1.5)
        |]
      )
);

module Line = (val NiceComponents.div(~debugName="Line", [|Raw("white-space", "pre")|]));

module LineNumber = (
  val NiceComponents.span(
        ~debugName="LineNumber",
        [|MinWidth(Rem(2.)), Display(InlineBlock), Raw("user-select", "none"), Color(Colors.darkGray)|]
      )
);

module Language = (
  val NiceComponents.span(
        ~debugName="Language",
        [|Raw("float", "right"), Color(Colors.red)|]
      )
);

let component = ReasonReact.statelessComponent("Code");

let make = (~text, ~language="re", _children) => {
  ...component,
  render: _self =>
    <Wrapper>
      <Language> (ele_of_str(language)) </Language>
      (
        ele_of_arr(
          text
          |> Js.String.split("\n")
          |> Array.mapi((i, line) =>
               <Line key=(string_of_int(i))>
                 <LineNumber> (ele_of_str(string_of_int(i))) </LineNumber>
                 (ele_of_str(line))
               </Line>
             )
        )
      )
    </Wrapper>
};
