open BsCountrySelect;

[%bs.raw {|require('bs-country-select/src/styles.css')|}];

let inputStyle = Css.(style([margin2(~v=px(8), ~h=zero)]));
let countrySelectCustomStyle = Css.(style([backgroundColor(red)]));

type state = {selectedCountry: option(string)};

type action =
  | ChangeSelectedCountry(option(string));

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,
  initialState: () => {selectedCountry: None},
  reducer: (action, _: state) =>
    switch (action) {
    | ChangeSelectedCountry(value) =>
      ReasonReact.Update({selectedCountry: value})
    },
  render: self =>
    <div>
      <h2> {ReasonReact.string("Country Select for Ahrefs")} </h2>
      <input className=inputStyle />
      <CountrySelect
        /* className=countrySelectCustomStyle */
        country=?{self.state.selectedCountry}
        onChange={country =>
          self.send(
            ChangeSelectedCountry(country->Belt.Option.map(c => c##value)),
          )
        }
      />
      <input className=inputStyle />
    </div>,
};
