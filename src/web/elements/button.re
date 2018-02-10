include (
  val NiceComponents.button(
    ~debugName="Button",
        [|
          Color(White),
          BackgroundColor(RGBa(219, 77, 63, 1.)),
          Display(InlineBlock),
          Padding(Rem(1.)),
          BorderRadius(Px(3))
        |]
      )
);
