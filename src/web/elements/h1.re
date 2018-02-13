open Theme;

include (
  val NiceComponents.h1(
        ~debugName="H1",
        [|
          Raw("font-size", Font.Size.huge),
          MarginBottom(Spacing.normal),
          MarginTop(Spacing.large),
          Color(Colors.red)
        |]
      )
);
