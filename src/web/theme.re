open Nice;

module Colors = {
  let red = Hex("db4d3f");
  let lightRed = Hex("F2826E");
  let secondary = Hex("f8faff");
  let white = White;
  let black = Hex("282C34");
  let gray = Hex("ABB2BF");
  let darkGray = Hex("5C6370");
};

module Font = {
  let family = "Karla, sans-serif";
  module Size = {
    let huge = "2rem";
    let large = "1.5rem";
    let normal = "1.25rem";
    let small = "1rem";
  };
};

module Spacing = {
  let normal = Rem(1.);
  let small = Rem(0.5);
  let none = Rem(0.);
  let large = Rem(2.0);
};

module Frame = {
  let borderRadius = Rem(0.3);
  module Shadow = {
    let normal = "0 10px 40px 0 rgba(62,57,107,0.07), 0 2px 9px 0 rgba(62,57,107,0.06)"; 
    let darker = "0 10px 40px 0 rgba(62,57,107,0.20), 0 2px 9px 0 rgba(62,57,107,0.20)";
    let red = "0 10px 40px 0 rgba(219,77,63,0.37), 0 2px 9px 0 rgba(219,77,63,0.36);"; 
  };
            
};

module Animation = {
  module Transition = {
    let normal = "0.25s ease";
  };
};
